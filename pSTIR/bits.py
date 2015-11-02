##    def generateImage(self, par):
##        status = pystir.generateImage\
##            (self.path, par, self.stdout, self.stderr, self.verb)
##        output = pystir.keyValue(par, 'output filename')
##        return [status, output]
##    def postFilter(self, fin, fout, par):
##        status = pystir.postFilter\
##            (self.path, fin, fout, par, self.stdout, self.stderr, self.verb) 
##        return status

##            status = pystir.executionStatus(handle)
##            if status != 0:
##                msg = pystir.executionError(handle)
##                file = pystir.executionErrorFile(handle)
##                line = pystir.executionErrorLine(handle)
##                pystir.deleteDataHandle(handle)
##                errorMsg = msg + ' at line ' + repr(line) + ' of ' + file
##                raise Error(errorMsg)
##            pystir.deleteDataHandle(handle)
##            return status
##            status = pystir.doOSMAPOSLReconstruction(par)
##            status = pystir.runOSMAPOSL\
##                (self.path, par, self.stdout, self.stderr, self.verb)

##    def compareImages(self, image_a, image_b):
##        status = pystir.compareImage\
##            (self.path, image_a, image_b, self.stdout, self.stderr, self.verb)
##        return status

##status = stir.compareImages\
##    ('test_image_PM_MRP_6.hv', 'my_test_image_PM_MRP_6.hv', -1, 0.0001)
##print('compareImages status:', status)

#second = stir.imageFromFile('my_test_image_PM_MRP_6.hv')

##try:
##    result = stir.imageComparisonResult(first, second, -1, 0.0005)
##    print('imageComparisonResult:', result)
##except:
##    print('unhandled exception occured')

#            handle = pystir.STIR_OSMAPOSLReconstructionResult(par)

#            pystir.deleteDataHandle(handle)
#            return status

##    @staticmethod
##    def compareImages(image_a, image_b, rimsize, tolerance):
##        handle = pystir.STIR_compareImagesResult\
##            (image_a, image_b, rimsize, tolerance)
##        status = _status(handle)
##        if status == 0:
##            status = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return status

#stir.path = 'C:/Users/wps46139/Codes/stirdev-stir-97723408086a/Release/'

##[status, output] = stir.generateImage('generate_uniform_image.par')
##print('generateImage status:', status)
##print('output file name:', output)
##if status != 0:
##    sys.exit()
##
##file1 = stir.cat(output, '.hv')
##file2 = stir.cat(output, '_circular.hv')
##
##status = stir.postFilter(file1, file2, 'postfilter_truncate_circular_FOV.par')
##print('postFilter status:', status)
##if status != 0:
##    sys.exit()

##status = stir.reconstruct('OSMAPOSL_test_PM_QP.par')
##print('reconstruct status:', status)
##
##status = stir.compareImages\
##    ('test_image_PM_QP_6.hv', 'my_test_image_PM_QP_6.hv')
##print('compareImages status:', status)

##stir.method = 'OSSPS'
##status = stir.reconstruct('OSSPS_test_PM_QP.par')
##print('reconstruct status:', status)
##
##status = stir.compareImages\
##    ('test_image_OSSPS_PM_QP_8.hv', 'my_test_image_OSSPS_PM_QP_8.hv')
##print('compareImages status:', status)

##stir.writeText(twh, 'ok\n')
##
##tp = stir.newTextPrinter('stdout')
##stir.setWriter(twh, tp)
##
##stir.writeText(twh, 'ok\n')
##

#result = stir.imageComparisonResult(first, second, -1, 0.0005)
#print('imageComparisonResult:', result)

#    status = 0

#    status = 1
#print('execution status:', status)
#if status != 0:
#    sys.exit()

##        elif self.method == 'OSSPS':
##            status = pystir.runOSSPS\
##                (self.path, par, self.stdout, self.stderr, self.verb)
##        else:
##            status = -1
##        return status

##    @staticmethod
##    def generateImage(par):
##        handle = pystir.STIR_generateImageResult(par)
##        status = _status(handle)
##        pystir.deleteDataHandle(handle)
##        output = pystir.keyValue(par, 'output filename')
##        return [status, output]
##    @staticmethod
##    def postFilter(fin, fout, par):
##        handle = pystir.STIR_postFilterResult(fin, fout, par) 
##        status = _status(handle)
##        pystir.deleteDataHandle(handle)
##        return status

##    @staticmethod
##    def imageComparisonResult(first, second, rimsize, tolerance):
##        handle = pystir.STIR_imageComparisonResult\
##                 (first, second, rimsize, tolerance)
##        status = _status(handle)
##        if status == 0:
##            status = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return status

#twh = stir.newWriterHandle()
#stir.setWriter(twh, tw)

#stir.deleteWriterHandle(twh)

#tw = stir.newWriter('output.txt') # to print to output.txt
#stir.deleteWriter(tw)

#tw = stir.newPrinter('cout') # to print to stdout
#dummy = pStir.writeTo('out.txt')
#dummy = pStir.printTo('cout')

#stir.deletePrinter(tw)

##def _status(handle):
##    status = pystir.executionStatus(handle)
##    if status != 0:
##        msg = pystir.executionError(handle)
##        file = pystir.executionErrorFile(handle)
##        line = pystir.executionErrorLine(handle)
##        pystir.deleteDataHandle(handle)
##        errorMsg =\
##            msg + ' exception thrown at line ' + repr(line) + ' of ' + file
##        raise error(errorMsg)
##    return status

##    @staticmethod
##    def newWriterHandle():
##        return pystir.newTextWriterHandle()
##    @staticmethod
##    def deleteWriterHandle(twh):
##        pystir.deleteTextWriterHandle(twh)
##    @staticmethod
##    def newWriter(filename):
##        h = pystir.newTextWriterHandle()
##        w = pystir.newTextWriter(filename)
##        pystir.setWriter(h, w)
##        pystir.deleteTextWriterHandle(h)
##        return w
##    @staticmethod
##    def newPrinter(s):
##        h = pystir.newTextWriterHandle()
##        p = pystir.newTextPrinter(s)
##        pystir.setWriter(h, p)
##        pystir.deleteTextWriterHandle(h)
##        return p
##    @staticmethod
##    def deleteWriter(w):
##        pystir.deleteTextWriter(w)
##    @staticmethod
##    def deletePrinter(p):
##        pystir.deleteTextPrinter(p)
##    @staticmethod
##    def setWriter(twh, tw):
##        pystir.setWriter(twh, tw)
##    @staticmethod
##    def writeText(twh, text):
##        pystir.writeText(twh, text)

##        ldest = dest.casefold()
##        if ldest == 'stdout' or ldest == 'stderr'\
##            or ldest == 'cout' or ldest == 'cerr':

##    if method == 'OSMAPOSL':
##        image_a = stir.imageFromFile('test_image_PM_MRP_6.hv')
##        image_b = stir.reconstructedImage('OSMAPOSL_test_PM_MRP.par')
##    elif method == 'OSSPS':
##        image_a = stir.imageFromFile('test_image_OSSPS_PM_QP_8.hv')
##        image_b = stir.reconstructedImage('OSSPS_test_PM_QP.par')
##    else:
##        image_b = stir.reconstructedImage('')


    #par = stir.reconstructionParameters(method)
    stir.printTo('rp.par')
##    stir.setParameter(par, 'map model', 'additive')
##    stir.setParameter(par, 'objective function type.input file', 'input.hs')
##    parname = 'inter-iteration filter type.Data Processor to apply first'
##    stir.setParameterList(par, parname,\
##        stir.truncateToCylindricalFOVParameters())
##    stir.setParameter(par, parname + '.strictly_less_than_radius', 1);
    stir.printParameters(par)
    stir.deleteParameters(par)

#    x = '1'
#    print(type(x))

##    par = stir.reconstructionParameters(method)
##    stir.setParameter(par, 'inter-iteration filter subiteration interval', 2)
##    stir.setParameter(par, 'start at subiteration number', 2)
##    stir.printTo('rp.par')
##    stir.printParameters(par)

    #stir.method = method
    #par = stir.reconstructionParameters(parFile)

    #stir.deleteParameters(par)

##    def reconstructedImage(self, par):
##        if self.method == 'OSMAPOSL':
##            if type(par) == type (' '):
##                handle = pystir.STIR_OSMAPOSLReconstruction(par)
##            else:
##                handle = pystir.STIR_OSMAPOSLReconstructedImage(par)
##            _check_status(handle)
##        elif self.method == 'OSSPS':
##            if type(par) == type (' '):
##                handle = pystir.STIR_OSSPSReconstruction(par)
##            else:
##                handle = pystir.STIR_OSSPSReconstructedImage(par)
##            _check_status(handle)
##        else:
##            raise error('unknown reconstruction algorithm ' + repr(self.method))
##        return handle

##    @staticmethod
##    def setInput(par, filename):
##        pystir.STIR_setParameter\
##            (par, 'objective function type.input file', filename)
##    @staticmethod
##    def setOutput(par, filename):
##        pystir.STIR_setParameter(par, 'output filename prefix', filename)
##    @staticmethod
##    def turnOn(par, name):
##        if pystir.STIR_setParameter(par, name, '1') == 0:
##            errorMsg = 'parameter ' + name + ' not found'
##            raise error(errorMsg)
##    @staticmethod
##    def turnOff(par, name):
##        if pystir.STIR_setParameter(par, name, '0') == 0:
##            errorMsg = 'parameter ' + name + ' not found'
##            raise error(errorMsg)
##    @staticmethod
##    def setParameter(par, name, value):
##        if type(value) == type(' '):
##            v = value
##        else:
##            v = repr(value)
##        if pystir.STIR_setParameter(par, name, v) == 0:
##            errorMsg = 'parameter ' + name + ' not found'
##            raise error(errorMsg)
##    @staticmethod
##    def setParameterList(par, name, value):
##        if pystir.STIR_setParameterList(par, name, value) == 0:
##            errorMsg = 'parameter ' + name + ' not found'
##            raise error(errorMsg)
##    @staticmethod
##    def printParameters(par):
##        pystir.STIR_printParameters(par)

##    @staticmethod
##    def reconstructionParameters(src):
##        if src == 'OSMAPOSL':
##            return pystir.STIR_OSMAPOSLReconstructionParameters()
##        elif src == 'OSSPS':
##            return pystir.STIR_OSSPSReconstructionParameters()
##        else:
##            return pystir.STIR_parametersFromFile(src)
##            #raise error('unknown reconstruction algorithm ' + repr(self.method))

##    @staticmethod
##    def truncateToCylindricalFOVParameters():
##        return pystir.STIR_TruncateToCylindricalFOVParameters()
##    @staticmethod
##    def quadraticPriorParameters():
##        return pystir.STIR_QuadraticPriorParameters()

##    def writeTo(self, filename):
##        self.printer = _writeTo(filename)

##        if method == 'OSMAPOSL':
##            pystir.STIR_deleteParameters(self._parameters)
##            self._parameters = pystir.STIR_OSMAPOSLReconstructionParameters()
##        elif method == 'OSSPS':
##            pystir.STIR_deleteParameters(self._parameters)
##            self._parameters = pystir.STIR_OSSPSReconstructionParameters()
##        else:
##            raise error('unknown reconstruction algorithm ' + repr(method))

##        if self._method == 'OSMAPOSL':
##            handle = pystir.STIR_OSMAPOSLReconstructedImage(self._parameters)
##            _check_status(handle)
##        elif self._method == 'OSSPS':
##            handle = pystir.STIR_OSSPSReconstructedImage(self._parameters)
##            _check_status(handle)
##        else:
##            raise error('unknown reconstruction algorithm ' + repr(self._method))

    #oft = 'objective function type'
    #stir.setParameter(oft + '.zero end planes of segment 0', 1)
    #stir.setParameter(stir.cat(oft, '.zero end planes of segment 0'), 1)

    #pmt = '.projector pair type.matrix type'

##    stir.setParameter('number of subsets', 4)
##    stir.setParameter('number of subiterations', 8)
##    stir.setParameter('save estimates at subiteration intervals', 8)
##    stir.setParameter('relaxation parameter', 2)
    #stir.setParameter('initial estimate', 'test_image_PM_QP_6.hv')

    stir.printParameters()

#stir.path = '..\\Data\\'

            #print(filename)

            #print(line)
            #print('iteration %d: images difference: %f\n', i, diff)

##    dim = pystir.intArray(3)
##    stir.getImageDimensions(firstImage, dim)
    #data = pystir.doubleArray(n)
    dim = numpy.ndarray((3,), dtype = numpy.int32)
    #print(dim.ctypes.data)
    stir.getImageDimensions(firstImage, dim.ctypes.data)
    nz = dim[0]
    ny = dim[1]
    nx = dim[2]
    print(nx)
    print(ny)
    print(nz)
    n = nx*ny*nz
    data = numpy.ndarray((nz, ny, nx), dtype = numpy.float64)
    stir.getImageData(firstImage, data.ctypes.data)
    print(data.shape)
    #section = data[0,:,:]
    #print(section.shape)
    #plt.imshow(section)
    #plt.show()
    for z in range(4):
        section = data[z,:,:]
        plt.imshow(section)
        plt.show()

##    dim = numpy.ndarray((3,), dtype = numpy.int32)
##    stir.getImageDimensions(reconstructedImage, dim.ctypes.data)
##    nz = dim[0]
##    ny = dim[1]
##    nx = dim[2]
##    print(nx)
##    print(ny)
##    print(nz)
##    data = numpy.ndarray((nz, ny, nx), dtype = numpy.float64)
##    stir.getImageData(reconstructedImage, data.ctypes.data)

class ObjectiveFunction:
    def __init__(self, recon):
        self.handle = pystir.cSTIR_parameter\
            (recon.handle, recon.method, 'objective_function')
        _check_status(self.handle)
    def set_sensitivity_filename(self, name):
        status = pystir.cSTIR_setParameter\
            (self.handle,\
             'PoissonLogLikelihoodWithLinearModelForMeanAndProjData',\
             'sensitivity_filename', name)
        if status != 0:
            errorMsg = 'parameter not found'
            raise error(errorMsg)

        if status != 0:
            errorMsg = 'parameter not found'
            raise error(errorMsg)

##        pystir.cSTIR_setParameter\
##            (self.handle, self.method, 'num_subsets', repr(n))

##        handle = pystir.cSTIR_parameter\
##            (self.handle, self.method, 'num_subsets')
##        _check_status(handle)
##        value = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return value

##        pystir.cSTIR_setParameter\
##            (self.handle, self.method, 'num_subiterations', repr(n))

##        handle = pystir.cSTIR_parameter\
##            (self.handle, self.method, 'num_subiterations')
##        _check_status(handle)
##        value = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return value

    n = recon.get_num_subsets()
    print('number of subsets:', n)
    n = recon.get_num_subiterations()
    print('number of subiterations:', n)
    recon.set_num_subiterations(n)
    m = recon.get_num_subiterations()
    print('number of subiterations:', m)

##    recon.update(image)
##    recon.update(image)
##    recon.update(image)
##    recon.update(image)
##    recon.update(image)
##    recon.update(image)

    pylab.figure()
    pylab.imshow(data[10,:,:])
    pylab.show()

import matplotlib.pyplot as plt

##        plt.figure(iter)
##        plt.imshow(section)
##    plt.show()

##        plt.figure(z)
##        plt.imshow(section)
##    plt.show()

        section = data[1,:,:]

        section = data[z,:,:]

##    def _set_num_par(self, name, n):
##        status = pystir.cSTIR_setParameter\
##            (self.handle, self.name, name, repr(n))
##        if status != 0:
##            errorMsg = 'parameter ' + name + ' not found'
##            raise error(errorMsg)
##    def _get_int_par(self, name):
##        handle = pystir.cSTIR_parameter\
##            (self.handle, self.name, name)
##        _check_status(handle)
##        value = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return value

        #self._set_num_par('num_subsets', n)

        #return self._get_int_par('num_subsets')

        #self._set_num_par('num_subiterations', n)

        #return self._get_int_par('num_subiterations')

        #self._set_num_par('start_subiteration_num', n)

        #return self._get_int_par('start_subiteration_num')

#import os
#import sys

##path = os.getenv('STIR_DATA_PATH')

##argc = len(sys.argv)
##if argc > 3:
##    output = sys.argv[1]
##    method = sys.argv[2]
##    parFile = sys.argv[3] + '.par'
##    if argc > 4:
##        expectedImageFile = path + '/' + sys.argv[4] + '.hv'
##    else:
##        expectedImageFile = ''
##else:
##    print('usage: stir_demo.py <output> <method> <parameters> [<image>]')
##    exit()

##    if len(expectedImageFile) > 0:

##    pylab.figure()
##    pylab.hold(True)

        # force recon.reconstruct to do iteration <iter> only
        # by making both the first iteration number and the
        # last iteration number equal to <iter>
##        recon.set_start_subiteration_num(iter)
##        recon.set_num_subiterations(iter)
##        recon.reconstruct(image)

##class printTo:
##    def __init__(self, dest):
##        h = pystir.newTextWriterHandle()
##        self.p = pystir.newTextPrinter(dest)
##        pystir.setWriter(h, self.p)
##        pystir.deleteTextWriterHandle(h)
##    def __del__(self):
##        pystir.deleteTextPrinter(self.p)
##
##class writeTo:
##    def __init__(self, dest):
##        h = pystir.newTextWriterHandle()
##        self.w = pystir.newTextWriter(dest)
##        pystir.setWriter(h, self.w)
##        pystir.deleteTextWriterHandle(h)
##    def __del__(self):
##        pystir.deleteTextWriter(self.w)

        #handle = pystir.cSTIR_reconstructionSetup(self.handle, image.handle)

##    def set_num_subsets(self, n):
##        _set_num_par(self, 'num_subsets', n)
##    def get_num_subsets(self):
##        return _get_int_par(self, 'num_subsets')
##    def set_num_subiterations(self, n):
##        _set_num_par(self, 'num_subiterations', n)
##    def get_num_subiterations(self):
##        return _get_int_par(self, 'num_subiterations')
##    def set_start_subiteration_num(self, n):
##        _set_num_par(self, 'start_subiteration_num', n)
##    def get_start_subiteration_num(self):
##        return _get_int_par(self, 'start_subiteration_num')
##    def get_objective_function(self):
##        obj_fun = PoissonLogLikelihoodWithLinearModelForMean3DFloat()
##        pystir.deleteDataHandle(obj_fun.handle)
##        obj_fun.handle = pystir.cSTIR_parameter\
##            (self.handle, self.name, 'objective_function')
##        _check_status(obj_fun.handle)
##        return obj_fun
##    def set_up(self, image):
##        handle = pystir.cSTIR_setupReconstruction\
##                 (self.name, self.handle, image.handle)
##        _check_status(handle)
##        pystir.deleteDataHandle(handle)
##    def reconstruct(self, image):
##        handle = pystir.cSTIR_reconstruct(self.handle, image.handle)
##        _check_status(handle)
##        pystir.deleteDataHandle(handle)
##    def set_subiteration_num(self, i):
##        handle = pystir.cSTIR_setSubiteration(self.name, self.handle, i)
##        _check_status(handle)
##        pystir.deleteDataHandle(handle)
##    def subiteration_num(self):
##        handle = pystir.cSTIR_getSubiteration(self.name, self.handle)
##        _check_status(handle)
##        iter = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return iter;
##    def update(self, image):
##        handle = pystir.cSTIR_update(self.name, self.handle, image.handle)
##        _check_status(handle)
##        pystir.deleteDataHandle(handle)

    #p = pystir.cSTIR_newInt(value)
    #handle = pystir.charDataHandleWrap(repr(value))

    #status = pystir.cSTIR_setParameter(handle, set, par, repr(value))
    #pystir.cSTIR_deleteInt(p);

        #value = pystir.cSTIR_charToVoid(name)

        #pystir.printCharData(handle)

        #set_num_par(self.handle, 'OSMAPOSL', 'num_subsets', n)

        #_set_num_par(self, 'num_subsets', n)

        #return _get_int_par(self, 'num_subsets')

        #_set_num_par(self, 'num_subiterations', n)

        #return _get_int_par(self, 'num_subiterations')

        #_set_num_par(self, 'start_subiteration_num', n)

        #return _get_int_par(self, 'start_subiteration_num')

            #(self.handle, self.name, 'objective_function')

#import ctypes
#from ctypes import *

    n = recon.get_num_subsets()
    print(n)

    data = stir.imageData(image)
    dmin = numpy.amin(data)
    dmax = numpy.amax(data)
    print(dmin, dmax)
    pylab.figure(1)
    pylab.imshow(data[10,:,:])
    pylab.show()

        if status != 0:
            errorMsg = 'parameter ' + 'prior' + ' not found'
            raise error(errorMsg)

##        h = pystir.cSTIR_parameter\
##            (value.handle, value.name, 'num_tangential_LORs')
##        v = pystir.intDataFromHandle(h)
##        print(v)
##        pystir.deleteDataHandle(h)

##        if status != 0:
##            errorMsg = 'parameter not found'
##            raise error(errorMsg)

##    def __init__(self):
##        self.name = 'GeneralisedPrior'
##        self.handle = pystir.newDataHandle()
##    def __del__(self):
##        pystir.deleteDataHandle(self.handle)

##    def __init__(self):
##        self.name = 'GeneralisedObjectiveFunction'
##        self.handle = pystir.newDataHandle()
##    def __del__(self):
##        pystir.deleteDataHandle(self.handle)

    # and assign values to parameters listed in 'OSMAPOSL_test_PM_MRP.par'
    #recon = stir.OSMAPOSLReconstruction3DFloat('OSMAPOSL_test_PM_MRP.par')
    #recon = stir.OSMAPOSLReconstruction3DFloat('OSMAPOSL_test_PM_QP.par')

    # any parameter can be changed manually, e.g.

    #recon.set_num_subiterations(0)

    n = recon.get_start_subset_num()
    print(n)

    #recon.set_initial_estimate_filename('my_uniform_image_circular.hv')

##    # get access to the objective function and change some parameters
##    poissonobj = recon.get_objective_function()
##    poissonobj.set_sensitivity_filename('RPTsens_seg3_PM.hv')
##    #poissonobj.set_recompute_sensitivity(True)
##    poissonobj.set_prior(prior)
##    recon.set_objective_function(obj_fun)
##    #recon.set_objective_function(poissonobj)

    #image.read_from_file('my_uniform_image.hv')

    # show initial image
    data = stir.imageData(image)
    pylab.figure(1)
    pylab.imshow(data[10,:,:])
    pylab.show()

    dmin = numpy.amin(data)
    dmax = numpy.amax(data)
    print(dmin, dmax)

    #expectedImage.read_from_file('test_image_PM_MRP_6.hv')

        #print(self.name)

        #handle = pystir.cSTIR_setupObjective(self.name, self.handle)

                 #(self.name, self.handle, image.handle)

        #handle = pystir.cSTIR_setSubiteration(self.name, self.handle, i)

        #handle = pystir.cSTIR_getSubiteration(self.name, self.handle)

        #handle = pystir.cSTIR_update(self.name, self.handle, image.handle)

        #super(IterativeReconstruction, self).__init__()

def _set_num_par(set, name, n):
    status = pystir.cSTIR_setParameter\
        (set.handle, set.name, name, repr(n))
    if status != 0:
        errorMsg = 'parameter ' + name + ' not found'
        raise error(errorMsg)
def _get_int_par(set, name):
    handle = pystir.cSTIR_parameter\
        (set.handle, set.name, name)
    _check_status(handle)
    value = pystir.intDataFromHandle(handle)
    pystir.deleteDataHandle(handle)
    return value

        if status != 0:
            errorMsg = 'parameter not found'
            raise error(errorMsg)

##        handle = pystir.cSTIR_setSubiteration(self.handle, i)
##        _check_status(handle)
##        pystir.deleteDataHandle(handle)

##    def set_initial_estimate_filename(self, name):
##        handle = pystir.charDataHandle(name)
##        pystir.cSTIR_setParameter\
##            (self.handle, self.name, 'initial_estimate', handle)
##        pystir.deleteDataHandle(handle)

    #pystir.cSTIR_setParameter(handle, set, par, h)

##    if status != 0:
##        errorMsg = 'parameter ' + par + ' not found'
##        raise error(errorMsg)

        #if dest.casefold() in {'stdout', 'stderr', 'cout', 'cerr'}:

        #pystir.cSTIR_setParameter\

        #pystir.cSTIR_setSubiteration(self.handle, i)

        #return pystir.cSTIR_getSubiteration(self.handle)
##        handle = pystir.cSTIR_getSubiteration(self.handle)
##        _check_status(handle)
##        iter = pystir.intDataFromHandle(handle)
##        pystir.deleteDataHandle(handle)
##        return iter;

        #h = pystir.intDataHandle(value)
        #_setParameter\
        #    (self.handle, 'RayTracingMatrix', 'num_tangential_LORs', h)
        #pystir.deleteDataHandle(h)

        #h = pystir.cSTIR_parameter\

        #value = pystir.intDataFromHandle(h)
        #pystir.deleteDataHandle(h)
        #return value

##        h = pystir.floatDataHandle(value)
##        _setParameter\
##            (self.handle, 'GeneralisedPrior', 'penalisation_factor', h)
##        pystir.deleteDataHandle(h)

##        h = pystir.cSTIR_parameter\
##            (self.handle, 'GeneralisedPrior', 'penalisation_factor')
##        value = pystir.floatDataFromHandle(h)
##        pystir.deleteDataHandle(h)
##        return value

##        handle = pystir.charDataHandle(name)
##        _setParameter\
##            (self.handle, 'PoissonLogLikelihoodWithLinearModelForMean',\
##             'sensitivity_filename', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(repr(flag))
##        _setParameter\
##            (self.handle, 'PoissonLogLikelihoodWithLinearModelForMean',\
##             'use_subset_sensitivities', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(repr(value))
##        _setParameter\
##            (self.handle, 'PoissonLogLikelihoodWithLinearModelForMean',\
##             'recompute_sensitivity', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(name)
##        _setParameter\
##            (self.handle, self.name, 'input_filename', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(repr(flag))
##        _setParameter\
##            (self.handle, self.name, 'zero_seg0_end_planes', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(prefix)
##        _setParameter\
##            (self.handle, 'Reconstruction', 'output_filename_prefix', handle)
##        pystir.deleteDataHandle(handle)

##    def set_initial_estimate_filename(self, name):
##        handle = pystir.charDataHandle(name)
##        _setParameter\
##            (self.handle, 'IterativeReconstruction', 'initial_estimate', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.charDataHandle(model)
##        _setParameter\
##            (self.handle, self.name, 'MAP_model', handle)
##        pystir.deleteDataHandle(handle)

##        handle = pystir.floatDataHandle(par)
##        _setParameter\
##            (self.handle, self.name, 'relaxation_parameter', handle)
##        pystir.deleteDataHandle(handle)

        #z = int(input('enter z-coordinate: '))

##    def __init__(self):
##        self.handle = pystir.newDataHandle()
##        self.name = 'GeneralisedObjectiveFunction'
##    def __del__(self):
##        pystir.deleteDataHandle(self.handle)

##    def __init__(self):
##        self.handle = pystir.newDataHandle()
##        self.name = 'IterativeReconstruction'
##    def __del__(self):
##        pystir.deleteDataHandle(self.handle)

##    def get_objective_function(self):
##        obj_fun = GeneralisedObjectiveFunction()
##        pystir.deleteDataHandle(obj_fun.handle)
##        obj_fun.handle = pystir.cSTIR_parameter\
##            (self.handle, 'IterativeReconstruction', 'objective_function')
##        _check_status(obj_fun.handle)
##        return obj_fun

def imageData(image):
    dim = numpy.ndarray((3,), dtype = numpy.int32)
    pystir.cSTIR_getImageDimensions(image.handle, dim.ctypes.data)
    nz = dim[0]
    ny = dim[1]
    nx = dim[2]
    data = numpy.ndarray((nz, ny, nx), dtype = numpy.float64)
    pystir.cSTIR_getImageData(image.handle, data.ctypes.data)
    return data

##    voxels = stir.Voxels3DFloat(60, 60, 31, 4.44114, 4.44114, 3.375)
##    voxels = stir.Voxels(100, 100, 50, 1, 1, 1)

    print(shape.get_radii())
##    shape.set_radius_x(30)
##    shape.set_radius_y(10)
##    print(shape.get_length())
##    print(shape.get_radius_x())
##    print(shape.get_radius_y())
##    my_origin = (0, 20, 10)
##    shape.set_origin(my_origin)

##    origin = shape.get_origin()
##    print(origin)

##    shape.set_radius_x(10)
##    shape.set_radius_y(10)

##    my_origin = (20, -10, 10)
##    shape.set_origin(my_origin)

##    my_origin = (-20, -10, 10)
##    shape.set_origin(my_origin)

##    dmin = numpy.amin(data)
##    dmax = numpy.amax(data)
##    print(dmin, dmax)

# OR
# read from file:
# image.read_from_file(filename)
# OR
# setup manually using STIR shapes:
# voxel_dim = (100, 100, 50)
# voxel_size = (1, 1, 1)
# voxels = stir.Voxels(voxel_dim, voxel_size)
# image.initialise_from_voxels(voxels)
# shape = stir.EllipsoidalCylinder()
# shape.set_length(40)
# shape.set_radii((30, 10))
# shape.set_origin((0, 20, 10))
# image.add_shape(voxels, shape, scale = 1)

##    def __init__(self, nx, ny, nz, sx, sy, sz, x = 0, y = 0, z = 0):
##        self.handle = pystir.cSTIR_voxels3DF(nx, ny, nz, sx, sy, sz, x, y, z)

projectors = stir.Projectors('projectors_parameters.par')
# OR:
# projectors = stir.Projectors('projectors using matrix')
# then set parameters manually

        ##handle =

##        pystir.deleteDataHandle(handle)
##        pystir.deleteDataHandle(self.handle)

        #self.ok = False

        #self.ok = True

##        elif isinstance(arg, Voxels):
##            self.handle = pystir.cSTIR_imageFromVoxels(arg.handle)
##            _check_status(self.handle)
##            self.empty = False

##    def get_from_voxels(self, voxels):
##        self.handle = pystir.cSTIR_imageFromVoxels(voxels.handle)
##        _check_status(self.handle)

##    def add_shape(self, voxels, shape, scale):

##                 (self.handle, voxels.handle, shape.handle, scale)

    voxels = stir.Voxels(voxel_dim, voxel_size)

    #image = stir.Image(voxels)
    #image.get_from_voxels(voxels)

    #image.add_shape(voxels, shape, scale = 1)

    #image.add_shape(voxels, shape, scale = 2)

    #image.add_shape(voxels, shape, scale = 0.25)

        #return RayTracingMatrix(self)

##        if proj is None:
##            self.handle = pystir.cSTIR_newObject(self.name);
##            self.owns_obj = True
##        else:
##            self.handle = _getParameterHandle\
##                (proj.handle, 'ProjectorsUsingMatrix', 'matrix_type')
##            self.owns_obj = False

##        if self.owns_obj:
##            pystir.cSTIR_deleteObject(self.handle, self.name)
##        else:
##            pystir.deleteDataHandle(self.handle)

##    def __init__(self, recon = None):
##        self.name = 'PoissonLogLikelihoodWithLinearModelForMean'
##        if recon is not None:
##            self.handle = _getParameterHandle\
##                (recon.handle, 'IterativeReconstruction', 'objective_function')

##    def get_objective_function(self):
##        return self.obj_fun
##        #return PoissonLogLikelihoodWithLinearModelForMean(self)

##            (self.handle, 'ProjectorsUsingMatrix', 'matrix_type', matrix.handle)

##            raise error('ProjectorsUsingMatrix: no matrix set')

##            (self.handle, 'RayTracingMatrix', 'num_tangential_LORs', value)

##            (self.handle, 'RayTracingMatrix', 'num_tangential_LORs')

##            err_msg = 'PoissonLogLikelihoodWithLinearModelForMeanAndProjData:'\
##                      + ' no projectors set'
##            raise error(err_msg)

##        _set_int_par(self.handle, 'IterativeReconstruction', 'num_subsets', n)

##        return _int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        return _int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        return _int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        return _int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        return _int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        _set_int_par(self.handle, 'IterativeReconstruction',\

##        _setParameter\
##            (self.handle, 'IterativeReconstruction',\
##             'objective_function', obj_fun.handle)

##            raise error('IterativeReconstruction: no objective function set')

##            (self.handle, 'IterativeReconstruction',\

##            raise error('IterativeReconstruction: no filter set')
