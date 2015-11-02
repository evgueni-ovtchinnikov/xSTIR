#include "dh.h"
#include "stir.h"
#include "stir_p.h"
#include "stir_x.h"

#define CAST_PTR(T, X, Y) T* X = (T*)Y
#define NEW_SPTR(T, X, ARG) boost::shared_ptr< T >* X = new boost::shared_ptr< T >(new T ARG)

template<class Method>
void* 
cSTIR_newReconstructionMethod(const char* parFile) 
{
	DataHandle* handle = new DataHandle;
	try {
		Method* recon; 
		if (strlen(parFile) > 0)
			recon = new Method(parFile);
		else
			recon = new Method();
		handle->set((void*)recon, 0);
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

template<class Base, class Object = Base>
static void*
newObjectHandle()
{
	DataHandle* handle = new DataHandle;
	boost::shared_ptr<Base>* pp = new boost::shared_ptr<Base>(new Object());
	handle->set((void*)pp, 0);
	return (void*)handle;
}

template<class Object>
static void
deleteObjectHandle(DataHandle* handle)
{
	if (!handle)
		return;
	CAST_PTR(boost::shared_ptr<Object>, sptr, handle->data());
	delete sptr;
	delete handle;
}

static void*
unknownObject(const char* obj, const char* set, const char* file, int line)
{
	DataHandle* handle = new DataHandle;
	std::string error = "unknown ";
	error += obj;
	error += " '";
	error += set;
	error += "'";
	ExecutionStatus status(error.c_str(), file, line);
	handle->set(0, &status);
	return (void*)handle;
}

extern "C"
void* cSTIR_newObject(const char* name)
{
	DataHandle* handle = new DataHandle;
	if (boost::iequals(name,
		"PoissonLogLikelihoodWithLinearModelForMeanAndProjData"))
		return newObjectHandle<GeneralisedObjectiveFunction<Image3DF>,
		PoissonLogLikelihoodWithLinearModelForMeanAndProjData<Image3DF> >
		();
	else if (boost::iequals(name, "ProjectorsUsingMatrix"))
		return newObjectHandle
		<ProjectorByBinPair, ProjectorByBinPairUsingProjMatrixByBin>();
	if (boost::iequals(name, "RayTracingMatrix"))
		return newObjectHandle
		<ProjMatrixByBin, ProjMatrixByBinUsingRayTracing>();
	else if (boost::iequals(name, "QuadraticPrior"))
		return newObjectHandle
		<GeneralisedPrior<Image3DF>, QuadraticPrior<float> >();
	else if (boost::iequals(name, "TruncateToCylindricalFOVImageProcessor"))
		return newObjectHandle<DataProcessor<Image3DF>,
		TruncateToCylindricalFOVImageProcessor<float> >();
	if (boost::iequals(name, "EllipsoidalCylinder"))
		return newObjectHandle<Shape3D, EllipsoidalCylinder>();
	else
		return unknownObject("object", name, __FILE__, __LINE__);
}

extern "C"
void cSTIR_deleteObject(void* ptr, const char* name)
{
	CAST_PTR(DataHandle, handle, ptr);
	if (boost::iequals(name,
		"PoissonLogLikelihoodWithLinearModelForMeanAndProjData"))
		deleteObjectHandle<GeneralisedObjectiveFunction<Image3DF> >
		(handle);
	else if (boost::iequals(name, "ProjectorsUsingMatrix"))
		deleteObjectHandle<ProjectorByBinPair>(handle);
	else if (boost::iequals(name, "RayTracingMatrix"))
		deleteObjectHandle<ProjMatrixByBin>(handle);
	else if (boost::iequals(name, "QuadraticPrior"))
		deleteObjectHandle<GeneralisedPrior<Image3DF> >(handle);
	else if (boost::iequals(name, "TruncateToCylindricalFOVImageProcessor"))
		deleteObjectHandle<DataProcessor<Image3DF> >(handle);
	else if (boost::iequals(name, "EllipsoidalCylinder"))
		deleteObjectHandle<Shape3D>(handle);
	else if (boost::iequals(name, "Image"))
		deleteObjectHandle<sptrImage3DF>(handle);
	else if (boost::iequals(name, "Voxels"))
		deleteObjectHandle<sptrVoxels3DF>(handle);
}

extern "C"
void* cSTIR_setParameter
(void* ptr_s, const char* set, const char* name, const void* ptr_v)
{
	CAST_PTR(DataHandle, hs, ptr_s);
	CAST_PTR(DataHandle, hv, ptr_v);
	if (boost::iequals(set, "Shape"))
		return cSTIR_setShapeParameter(hs, name, hv);
	else if (boost::iequals(set, "EllipsoidalCylinder"))
		return cSTIR_setEllipsoidalCylinderParameter(hs, name, hv);
	else if (boost::iequals(set, "ProjectorsUsingMatrix"))
		return cSTIR_setProjectorsUsingMatrixParameter(hs, name, hv);
	else if (boost::iequals(set, "RayTracingMatrix"))
		return cSTIR_setRayTracingMatrixParameter(hs, name, hv);
	else if (boost::iequals(set, "GeneralisedPrior"))
		return cSTIR_setGeneralisedPriorParameter(hs, name, hv);
	else if (boost::iequals(set, "QuadraticPrior"))
		return cSTIR_setQuadraticPriorParameter(hs, name, hv);
	else if (boost::iequals(set, "GeneralisedObjectiveFunction"))
		return cSTIR_setGeneralisedObjectiveFunctionParameter(hs, name, hv);
	else if (boost::iequals(set, "PoissonLogLikelihoodWithLinearModelForMean"))
		return cSTIR_setPoissonLogLikelihoodWithLinearModelForMeanParameter
		(hs, name, hv);
	else if (boost::iequals(set,
		"PoissonLogLikelihoodWithLinearModelForMeanAndProjData"))
		return
		cSTIR_setPoissonLogLikelihoodWithLinearModelForMeanAndProjDataParameter
		(hs, name, hv);
	else if (boost::iequals(set, "Reconstruction"))
		return cSTIR_setReconstructionParameter(hs, name, hv);
	else if (boost::iequals(set, "IterativeReconstruction"))
		return cSTIR_setIterativeReconstructionParameter(hs, name, hv);
	else if (boost::iequals(set, "OSMAPOSL"))
		return cSTIR_setOSMAPOSLParameter(hs, name, hv);
	else if (boost::iequals(set, "OSSPS"))
		return cSTIR_setOSSPSParameter(hs, name, hv);
	else
		return unknownObject("parameter set", set, __FILE__, __LINE__);
}

extern "C"
void* cSTIR_parameter(const void* ptr, const char* set, const char* name) 
{
	CAST_PTR(DataHandle, handle, ptr);
	if (boost::iequals(set, "Shape"))
		return cSTIR_shapeParameter(handle, name);
	if (boost::iequals(set, "EllipsoidalCylinder"))
		return cSTIR_ellipsoidalCylinderParameter(handle, name);
	if (boost::iequals(set, "RayTracingMatrix"))
		return cSTIR_rayTracingMatrixParameter(handle, name);
	if (boost::iequals(set, "ProjectorsUsingMatrix"))
		return cSTIR_projectorsUsingMatrixParameter(handle, name);
	if (boost::iequals(set, "GeneralisedPrior"))
		return cSTIR_generalisedPriorParameter(handle, name);
	if (boost::iequals(set, "IterativeReconstruction"))
		return cSTIR_iterativeReconstructionParameter(handle, name);
	if (boost::iequals(set, "OSMAPOSL"))
		return cSTIR_OSMAPOSLParameter(handle, name);
	if (boost::iequals(set, "OSSPS"))
		return cSTIR_OSSPSParameter(handle, name);
	return unknownObject("parameter set", set, __FILE__, __LINE__);
}

extern "C"
void* cSTIR_newReconstruction(const char* method, const char* filename)
{
	void* recon;
	if (boost::iequals(method, "OSMAPOSL"))
		recon = cSTIR_newReconstructionMethod<OSMAPOSLReconstruction<Image3DF> >
		(filename);
	else if (boost::iequals(method, "OSSPS"))
		recon = cSTIR_newReconstructionMethod<OSSPSReconstruction<Image3DF> >
		(filename);
	else
		recon = unknownObject("method", method, __FILE__, __LINE__);
	return recon;
}

extern "C"
void* cSTIR_setupObject(const char* obj, void* ptr_obj)
{
	CAST_PTR(DataHandle, ho, ptr_obj);
	DataHandle* handle = new DataHandle;
	try {
		bool status = 1;
		//if (boost::iequals(obj, "prior"))
		if (boost::iequals(obj, "GeneralisedPrior"))
			status = xSTIR_setupPrior(ho->data());
		//else if (boost::iequals(obj, "objective_function"))
		else if (boost::iequals(obj, "GeneralisedObjectiveFunction"))
			status = xSTIR_setupObjectiveFunction(ho->data());
		if (status) {
			ExecutionStatus status("cSTIR_setupObject failed", __FILE__, __LINE__);
			handle->set(0, &status);
			return (void*)handle;
		}
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

extern "C"
void* cSTIR_setupReconstruction(void* ptr_r, void* ptr_i)
{
	CAST_PTR(DataHandle, hr, ptr_r);
	CAST_PTR(DataHandle, hi, ptr_i);
	CAST_PTR(sptrImage3DF, image, hi->data());
	DataHandle* handle = new DataHandle;
	try {
		Succeeded s = xSTIR_setupReconstruction(hr->data(), *image);
		if (s != Succeeded::yes) {
			ExecutionStatus status("cSTIR_setupReconstruction failed",
				__FILE__, __LINE__);
			handle->set(0, &status);
		}
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

extern "C"
void* cSTIR_reconstruct(void* ptr_r, void* ptr_i) 
{
	CAST_PTR(DataHandle, hr, ptr_r);
	CAST_PTR(DataHandle, hi, ptr_i);
	CAST_PTR(Reconstruction<Image3DF>, recon, hr->data());
	CAST_PTR(sptrImage3DF, image, hi->data());
	DataHandle* handle = new DataHandle;
	try {
		if (recon->reconstruct(*image) != Succeeded::yes) {
			ExecutionStatus status("cSTIR_reconstruct failed",
				__FILE__, __LINE__);
			handle->set(0, &status);
		}
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

extern "C"
void cSTIR_deleteReconstruction(void* ptr_r)
{
	if (!ptr_r)
		return;
	CAST_PTR(DataHandle, hr, ptr_r);
	CAST_PTR(Reconstruction<Image3DF>, recon, hr->data());
	delete recon;
	delete hr;
}

extern "C"
void* cSTIR_update(void* ptr_r, void* ptr_i)
{
	CAST_PTR(DataHandle, hr, ptr_r);
	CAST_PTR(DataHandle, hi, ptr_i);
	CAST_PTR(IterativeReconstruction<Image3DF>, recon, hr->data());
	CAST_PTR(sptrImage3DF, image, hi->data());
	DataHandle* handle = new DataHandle;
	try {
		xSTIR_updateReconstruction(hr->data(), **image);
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

extern "C"
void* cSTIR_voxels3DF
(int nx, int ny, int nz,
double sx, double sy, double sz,
double x, double y, double z)
{
	sptrVoxels3DF* sptr = new sptrVoxels3DF(
		new Voxels3DF(IndexRange3D(0, nz - 1,
			-(ny / 2), -(ny / 2) + ny - 1, -(nx / 2), -(nx / 2) + nx - 1),
			Coord3DF((float)z, (float)y, (float)x),
			Coord3DF((float)sz, (float)sy, (float)sx)));
	DataHandle* handle = new DataHandle;
	handle->set((void*)sptr, 0);
	return (void*)handle;
}

extern "C"
void* cSTIR_imageFromVoxels(void* ptr_v)
{
	CAST_PTR(DataHandle, hv, ptr_v);
	CAST_PTR(sptrVoxels3DF, sptr_v, hv->data());
	sptrImage3DF* sptr = new sptrImage3DF((*sptr_v)->clone());
	DataHandle* handle = new DataHandle;
	handle->set((void*)sptr, 0);
	return (void*)handle;
}

extern "C"
void* cSTIR_addShape(void* ptr_i, void* ptr_v, void* ptr_s, float v) 
{
	CAST_PTR(DataHandle, hi, ptr_i);
	CAST_PTR(DataHandle, hv, ptr_v);
	CAST_PTR(DataHandle, hs, ptr_s);
	CAST_PTR(sptrImage3DF, sptr_i, hi->data());
	CAST_PTR(sptrVoxels3DF, sptr_v, hv->data());
	CAST_PTR(sptrShape3D, sptr_s, hs->data());
	CartesianCoordinate3D<int> num_samples(1,1,1);

	Image3DF& image = *sptr_i->get();
	Voxels3DF& voxels = *sptr_v->get();
	voxels.fill(0);
	(*sptr_s)->construct_volume(voxels, num_samples);
	voxels *= v;
	image += voxels;

	return new DataHandle;
}

extern "C"
void* cSTIR_imageFromFile(const char* filename) 
{
	DataHandle* handle = new DataHandle;
	try {
		sptrImage3DF* ptr = new sptrImage3DF(read_from_file<Image3DF>(filename));
		handle->set((void*)ptr, 0);
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	catch (...) {
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}
	return (void*)handle;
}

extern "C"
void cSTIR_getImageDimensions(const void* ptr, size_t pd) 
{
	CAST_PTR(DataHandle, handle, ptr);
	CAST_PTR(sptrImage3DF, sptrImage, handle->data());
	sptrImage3DF& image = *sptrImage;
	Coordinate3D<int> min_indices;
	Coordinate3D<int> max_indices;
	int* dim = (int*)pd;
	if (!image->get_regular_range(min_indices, max_indices)) {
		//cout << "image is not regular" << endl;
		dim[0] = 0;
		dim[1] = 0;
		dim[2] = 0;
	}
	else {
		for (int i = 0; i < 3; i++)
			dim[i] = max_indices[i + 1] - min_indices[i + 1] + 1;
	}
}

extern "C"
void cSTIR_getImageData(const void* ptr, size_t pd) 
{
	CAST_PTR(DataHandle, handle, ptr);
	CAST_PTR(sptrImage3DF, sptrImage, handle->data());
	sptrImage3DF& image = *sptrImage;
	Coordinate3D<int> min_indices;
	Coordinate3D<int> max_indices;
	double* data = (double*)pd;
	if (!image->get_regular_range(min_indices, max_indices)) {
		//cout << "image is not regular" << endl;
		return;
	}
	else {
		for (int z = min_indices[1], i = 0; z <= max_indices[1]; z++) {
			for (int y = min_indices[2]; y <= max_indices[2]; y++) {
				for (int x = min_indices[3]; x <= max_indices[3]; x++, i++) {
					data[i] = (*image)[z][y][x];
				}
			}
		}
	}
}

extern "C"
void* cSTIR_imagesDifference(void* first, void* second, int rimsize) 
{
	DataHandle* handle = new DataHandle;
	try {

		CAST_PTR(DataHandle, first_h, first);
		CAST_PTR(DataHandle, second_h, second);
		CAST_PTR(sptrImage3DF, first_ptr, first_h->data());
		CAST_PTR(sptrImage3DF, second_ptr, second_h->data());

		sptrImage3DF& first_operand = *first_ptr;
		sptrImage3DF& second_operand = *second_ptr;

		{
			std::string explanation;
			if (!first_operand->has_same_characteristics(*second_operand,
				explanation))
			{
				warning("input images do not have the same characteristics.\n%s",
					explanation.c_str());
				ExecutionStatus status(
					"input images do not have the same characteristics",
					__FILE__, __LINE__);
				handle->set(0, &status);
				return (void*)handle;
			}
		}

		if (rimsize >= 0)
		{
			truncate_rim(*first_operand, rimsize);
			truncate_rim(*second_operand, rimsize);
		}

		float reference_max = first_operand->find_max();
		float reference_min = first_operand->find_min();

		float amplitude = fabs(reference_max) > fabs(reference_min) ?
			fabs(reference_max) : fabs(reference_min);

		*first_operand -= *second_operand;
		const float max_error = first_operand->find_max();
		const float min_error = first_operand->find_min();

		float max_abs_error = fabs(min_error);
		if (max_error > max_abs_error)
			max_abs_error = max_error;
		*first_operand += *second_operand;

		double* result = (double*)malloc(sizeof(double));
		*result = max_abs_error / amplitude;
		handle->set(result, 0, GRAB);
	}
	catch (StirException& se) {
		ExecutionStatus status(se);
		handle->set(0, &status);
	}
	//catch (exception& e) {
	//	cout << "exception " << e.what() << endl;
	//}
	catch (...) {
		//cout << "unhandled exception occured" << endl;
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);
		handle->set(0, &status);
	}

	return (void*)handle;
}
