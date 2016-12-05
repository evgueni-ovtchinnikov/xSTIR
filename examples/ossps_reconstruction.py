import argparse
import numpy
import pylab
import os
import sys
sys.path.append(os.environ.get('CSTIR_SRC') + '/../pSTIR')

from pStir import *

parser = argparse.ArgumentParser(description = \
'''
OSSPS reconstruction demo with all parameters defined in the script
and user-controlled iterations
''')
args = parser.parse_args()

def main():

    # direct all diagnostic printing to a file
    printer = printerTo('output.txt')

    # create matrix to be used by projectors
    matrix = RayTracingMatrix()
    matrix.set_num_tangential_LORs(2)
    n = matrix.get_num_tangential_LORs()

    # create acquisition model
    am = AcquisitionModelUsingMatrix()
    am.set_matrix(matrix)

    # read acquisition model data
    ad = AcquisitionData('Utahscat600k_ca_seg4.hs')

    # create prior
    prior = QuadraticPrior()
    prior.set_penalisation_factor(0.5)

    # create objective function
    obj_fun = PoissonLogLh_LinModMean_AcqMod()
    obj_fun.set_sensitivity_filename('RPTsens_seg3_PM.hv')
    obj_fun.set_recompute_sensitivity(True)
    obj_fun.set_use_subset_sensitivities(False)
    obj_fun.set_zero_seg0_end_planes(True)
    obj_fun.set_max_segment_num_to_process(3)
    obj_fun.set_acquisition_model(am)
    obj_fun.set_acquisition_data(ad)
    obj_fun.set_prior(prior)

    # create OSSPS reconstructor
    recon = OSSPSReconstruction()
    recon.set_num_subsets(4)
    recon.set_num_subiterations(8)
    recon.set_save_interval(8)
    recon.set_relaxation_parameter(2)
    recon.set_objective_function(obj_fun)

    # read an initial estimate for the reconstructed image from a file
    image = Image()
    image.read_from_file('test_image_PM_QP_6.hv')

    # set up the reconstructor
    print('setting up, please wait...')
    recon.set_up(image)

    # obtain the subiterations range
    start = recon.get_start_subiteration_num()
    stop = recon.get_num_subiterations()
    print('subiteration range: %d to %d' % (start, stop))

    # in order to see the reconstructed image evolution
    # take over the control of the iterative process
    # rather than allow recon.reconstruct to do all job at once

    # not needed (set by set_up), just to show we can start at any iteration 
    recon.set_subiteration_num(start)
    for iter in range(start, stop + 1):
        print('\n------------- Subiteration %d' % recon.get_subiteration_num())
        # perform an iteration
        recon.update(image)
        # plot the current image
        data = image.as_array()
        pylab.figure(iter)
        pylab.imshow(data[10,:,:])
        print('close Figure %d window to continue' % iter)
        pylab.show()

    # compare the reconstructed image to the expected image
    expectedImage = Image()
    expectedImage.read_from_file('test_image_OSSPS_PM_QP_8.hv')
    diff = expectedImage.diff_from(image)
    print('difference from expected image: %e' % diff)

    # let the user inspect any z-crossections of the image they want to
    data = image.as_array()
    nz = data.shape[0]
    print('Enter z-coordinate of the slice to view it')
    print('(a value outside the range [0 : %d] will stop the loop)'%(nz - 1))
    while True:
        s = str(input('z-coordinate: '))
        if len(s) < 1:
            break
        z = int(s)
        if z < 0 or z >= nz:
            break
        pylab.figure(z)
        pylab.imshow(data[z,:,:])
        print('close Figure %d window to continue' % z)
        pylab.show()

# if anything goes wrong, an exception will be thrown 
# (cf. Error Handling section in the spec)
try:
    main()
except error as err:
    # display error information
    print('STIR exception occured: %s' % err.value)
