% Steepest ascent demo

set_up_pet

try
    % info() printing suppressed, warning() and error() print to stdout
    printer = Printer();

    % create empty image
    image = Image();
    image_size = [111, 111, 31];
    voxel_size = [3, 3, 3.375];
    image.initialise(image_size, voxel_size)
    image.fill(1.0)

    % define a filter
    filter = CylindricFilter();
    filter.apply(image)

    % define acquisition data
    ad = AcquisitionData('my_forward_projection.hs');

    % define the matrix to be used by the acquisition model
    matrix = RayTracingMatrix();
    matrix.set_num_tangential_LORs(2)

    % define the acquisition model
    am = AcquisitionModelUsingMatrix();
    am.set_matrix(matrix)

    % define a prior
    prior = QuadraticPrior();
    prior.set_penalisation_factor(0.001)

    % define the objective function
    obj_fun = PoissonLogLh_LinModMean_AcqModData();
    obj_fun.set_zero_seg0_end_planes(true)
    obj_fun.set_max_segment_num_to_process(3)
    obj_fun.set_acquisition_model(am)
    obj_fun.set_acquisition_data(ad)
    obj_fun.set_prior(prior)
    obj_fun.set_num_subsets(12)
    obj_fun.set_up(image)

    z = 20;
    
    % plot the image
    idata = image.as_array();
    figure(1)
    imshow(idata(:,:,z));
    
    eps = 1.0e-6;
    tau = 0.3;
    
    v = obj_fun.value(image);
    fprintf('initial objective function value: %e\n', v);
    
    for iter = 1 : 3

        % obtain the gradient
        grad = obj_fun.gradient(image, 0);
        filter.apply(grad)
        gdata = grad.as_array();

        max_image = max(max(max(idata)));
        max_grad = max(max(max(abs(gdata))));

        % find maximal steepest descent step parameter t in image + t*grad 
        % such that the new image remains positive
        gdata(abs(gdata) < eps) = eps;
        r = idata./gdata;
        gdata(idata < 0) = 0;
        d = r(r < 0);
        if numel(d) > 0
            maxstep = -max(max(max(d)));
        else
            maxstep = tau*max_image/max_grad;
        end
        
        t = min(maxstep, tau*max_image/max_grad);

        % perform steepest descent step
        fprintf('step %d, max change in image %e\n', iter, t*max_grad);
        idata = idata + t*gdata;
        image.fill(idata);
        filter.apply(image);

        idata = image.as_array();
        figure(iter + 1)
        imshow(idata(:,:,z));

    end

    v = obj_fun.value(image);
    fprintf('final objective function value: %e\n', v);
    
catch err
    % display error information
    fprintf('??? %s\n', err.message)
    fprintf('error id is %s\n', err.identifier)
end
