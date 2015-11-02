#include <stdio.h>
#include <stdlib.h>

#include "cstir.h"
#include "dh.h"
#include "stir.h"
#include "stir_x.h"

#define CAST_PTR(T, X, Y) T* X = (T*)Y
#define NEW(T, X) T* X = new T

typedef CartesianCoordinate3D<float> Coord3DF;

static void*
parameterNotFound(const char* name, const char* file, int line) 
{
	DataHandle* handle = new DataHandle;
	std::string error = "parameter ";
	error += name;
	error += " not found";
	ExecutionStatus status(error.c_str(), file, line);
	handle->set(0, &status);
	return (void*)handle;
}

static void*
wrongParameterValue
(const char* name, const char* value, const char* file, int line)
{
	DataHandle* handle = new DataHandle;
	std::string error = "parameter ";
	error += name;
	error += " cannot be ";
	//error += " has wrong value ";
	error += value;
	ExecutionStatus status(error.c_str(), file, line);
	handle->set(0, &status);
	return (void*)handle;
}

static void*
wrongIntParameterValue
(const char* name, int value, const char* file, int line)
{
	char buff[32];
	sprintf(buff, "%d", value);
	return wrongParameterValue(name, buff, file, line);
}

static void*
wrongFloatParameterValue
(const char* name, float value, const char* file, int line)
{
	char buff[32];
	sprintf(buff, "%f", value);
	return wrongParameterValue(name, buff, file, line);
}

template<class Base, class Object = Base>
static Object*
objectFromHandle(const DataHandle* handle) {
	CAST_PTR(boost::shared_ptr<Base>, sptr, handle->data());
	CAST_PTR(Object, object, sptr->get());
	return object;
}

void*
cSTIR_setShapeParameter(DataHandle* hp, const char* name, const DataHandle* hv)
{
	Shape3D* s = objectFromHandle<Shape3D>(hp);
	Coord3DF origin = s->get_origin();
	float value = floatDataFromHandle(hv);
	if (boost::iequals(name, "x"))
		origin.x() = value;
	else if (boost::iequals(name, "y"))
		origin.y() = value;
	else if (boost::iequals(name, "z"))
		origin.z() = value;
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	s->set_origin(origin);
	return new DataHandle;
}

void*
cSTIR_shapeParameter(DataHandle* handle, const char* name)
{
	Shape3D* s = objectFromHandle<Shape3D>(handle);
	Coord3DF origin = s->get_origin();
	if (boost::iequals(name, "x"))
		return floatDataHandle(origin.x());
	else if (boost::iequals(name, "y"))
		return floatDataHandle(origin.y());
	else if (boost::iequals(name, "z"))
		return floatDataHandle(origin.z());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
}

void*
cSTIR_setEllipsoidalCylinderParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	EllipsoidalCylinder* c =
		objectFromHandle<Shape3D, EllipsoidalCylinder>(hp);
	float value;
	if (boost::iequals(name, "length")) {
		if ((value = floatDataFromHandle(hv)) < 1)
			return wrongFloatParameterValue("EllipsoidalCylinder::length",
			value, __FILE__, __LINE__);
		c->set_length(value);
	}
	else if (boost::iequals(name, "radius_x")) {
		if ((value = floatDataFromHandle(hv)) < 1)
			return wrongFloatParameterValue("EllipsoidalCylinder::radius_x",
			value, __FILE__, __LINE__);
		c->set_radius_x(value);
	}
	else if (boost::iequals(name, "radius_y")) {
		if ((value = floatDataFromHandle(hv)) < 1)
			return wrongFloatParameterValue("EllipsoidalCylinder::radius_y",
			value, __FILE__, __LINE__);
		c->set_radius_y(value);
	}
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_ellipsoidalCylinderParameter(const DataHandle* handle, const char* name)
{
	EllipsoidalCylinder* c =
		objectFromHandle<Shape3D, EllipsoidalCylinder>(handle);
	if (boost::iequals(name, "length"))
		return floatDataHandle(c->get_length());
	if (boost::iequals(name, "radius_x"))
		return floatDataHandle(c->get_radius_x());
	if (boost::iequals(name, "radius_y"))
		return floatDataHandle(c->get_radius_y());
	return parameterNotFound(name, __FILE__, __LINE__);
}

void*
cSTIR_setRayTracingMatrixParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	ProjMatrixByBinUsingRayTracing* matrix =
		objectFromHandle<ProjMatrixByBin, ProjMatrixByBinUsingRayTracing>(hp);
	int value;
	if (boost::iequals(name, "num_tangential_LORs")) {
		if ((value = intDataFromHandle(hv)) < 1)
			return wrongIntParameterValue
			("ProjMatrixByBinUsingRayTracing::num_tangential_LORs",
			value, __FILE__, __LINE__);
		matrix->set_num_tangential_LORs(value);
	}
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_rayTracingMatrixParameter(const DataHandle* handle, const char* name)
{
	ProjMatrixByBinUsingRayTracing* matrix =
		objectFromHandle<ProjMatrixByBin, 
		ProjMatrixByBinUsingRayTracing>(handle);
	if (boost::iequals(name, "num_tangential_LORs"))
		return intDataHandle(matrix->get_num_tangential_LORs());
	return parameterNotFound(name, __FILE__, __LINE__);
}

void*
cSTIR_setProjectorsUsingMatrixParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	ProjectorByBinPairUsingProjMatrixByBin* proj =
		objectFromHandle<ProjectorByBinPair, 
		ProjectorByBinPairUsingProjMatrixByBin>(hp);
	if (boost::iequals(name, "matrix_type"))
		proj->set_proj_matrix_sptr
		(*(boost::shared_ptr<ProjMatrixByBin>*)hv->data());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_projectorsUsingMatrixParameter(const DataHandle* handle, const char* name)
{
	ProjectorByBinPairUsingProjMatrixByBin* proj =
		objectFromHandle<ProjectorByBinPair,
		ProjectorByBinPairUsingProjMatrixByBin>(handle);
	if (boost::iequals(name, "matrix_type")) {
		NEW(DataHandle, h);
		NEW(boost::shared_ptr<ProjMatrixByBin>, sptr);
		*sptr = proj->get_proj_matrix_sptr();
		h->set((void*)sptr, 0);
		return (void*)h;
	}
	return parameterNotFound(name, __FILE__, __LINE__);
}

void*
cSTIR_setGeneralisedPriorParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(boost::shared_ptr<GeneralisedPrior<Image3DF> >, prior, hp->data());
	if (boost::iequals(name, "penalisation_factor"))
		(*prior)->set_penalisation_factor(floatDataFromHandle((void*)hv));
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_generalisedPriorParameter(const DataHandle* handle, std::string name)
{
	CAST_PTR(boost::shared_ptr<GeneralisedPrior<Image3DF> >, 
		prior, handle->data());
	if (boost::iequals(name, "penalisation_factor"))
		return floatDataHandle((*prior)->get_penalisation_factor());
	return parameterNotFound(name.c_str(), __FILE__, __LINE__);
}

void*
cSTIR_setQuadraticPriorParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	xSTIR_QuadraticPrior3DF* prior =
		objectFromHandle<GeneralisedPrior<Image3DF>, xSTIR_QuadraticPrior3DF>(hp);
	if (boost::iequals(name, "only_2D"))
		prior->only2D(intDataFromHandle((void*)hv));
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_setGeneralisedObjectiveFunctionParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(boost::shared_ptr<GeneralisedObjectiveFunction<Image3DF> >, 
		sptr, hp->data());
	if (boost::iequals(name, "prior"))
		(*sptr)->set_prior_sptr
			(*(boost::shared_ptr<GeneralisedPrior<Image3DF> >*)hv->data());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_setPoissonLogLikelihoodWithLinearModelForMeanParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	PoissonLogLikelihoodWithLinearModelForMean<Image3DF>*
		obj_fun = objectFromHandle<GeneralisedObjectiveFunction<Image3DF>,
		PoissonLogLikelihoodWithLinearModelForMean<Image3DF> >
		(hp);
	if (boost::iequals(name, "sensitivity_filename")) {
		obj_fun->set_sensitivity_filename((char*)hv->data());
	}
	else if (boost::iequals(name, "use_subset_sensitivities"))
		obj_fun->set_use_subset_sensitivities
			(boost::iequals((char*)hv->data(), "true"));
	else if (boost::iequals(name, "recompute_sensitivity"))
		obj_fun->set_recompute_sensitivity
			(boost::iequals((char*)hv->data(), "true"));
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_setPoissonLogLikelihoodWithLinearModelForMeanAndProjDataParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	xSTIR_PoissonLogLikelihoodWithLinearModelForMeanAndProjData3DF*
		obj_fun =
		objectFromHandle<GeneralisedObjectiveFunction<Image3DF>,
		xSTIR_PoissonLogLikelihoodWithLinearModelForMeanAndProjData3DF>
		(hp);
	if (boost::iequals(name, "input_filename"))
		obj_fun->set_input_file((char*)hv->data());
	else if (boost::iequals(name, "zero_seg0_end_planes"))
		obj_fun->set_zero_seg0_end_planes
			(boost::iequals((char*)hv->data(), "true"));
	else if (boost::iequals(name, "max_segment_num_to_process"))
		obj_fun->set_max_segment_num_to_process(intDataFromHandle((void*)hv));
	else if (boost::iequals(name, "projector_pair_type"))
		obj_fun->set_projector_pair_sptr
			(*(boost::shared_ptr<ProjectorByBinPairUsingProjMatrixByBin>*)hv->data());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_setReconstructionParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(Reconstruction<Image3DF>, recon, hp->data());
	if (boost::iequals(name, "output_filename_prefix"))
		recon->set_output_filename_prefix((char*)hv->data());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void*
cSTIR_setIterativeReconstructionParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(IterativeReconstruction<Image3DF>, recon, hp->data());
	if (boost::iequals(name, "inter_iteration_filter_type")) {
		CAST_PTR(boost::shared_ptr<DataProcessor<Image3DF> >, sptr, hv->data());
		recon->set_inter_iteration_filter_ptr(*sptr);
	}
	else if (boost::iequals(name, "objective_function")) {
		CAST_PTR(boost::shared_ptr<GeneralisedObjectiveFunction<Image3DF> >,
			sptr, hv->data());
		recon->set_objective_function_sptr(*sptr);
	}
	else if (boost::iequals(name, "initial_estimate"))
		xSTIR_set_initial_estimate_file(hp->data(), (char*)hv->data());
	else {
		int value = intDataFromHandle((void*)hv);
		if (boost::iequals(name, "num_subsets")) {
			if (value < 1)
				return wrongIntParameterValue("IterativeReconstruction::num_subsets",
				value, __FILE__, __LINE__);
			recon->set_num_subsets(value);
		}
		else if (boost::iequals(name, "start_subset_num")) {
			if (value < 0 || value >= recon->get_num_subsets())
				return wrongIntParameterValue
				("IterativeReconstruction::start_subset_num",
				value, __FILE__, __LINE__);
			recon->set_start_subset_num(value);
		}
		else if (boost::iequals(name, "num_subiterations")) {
			if (value < 1)
				return wrongIntParameterValue
				("IterativeReconstruction::num_subiterations",
				value, __FILE__, __LINE__);
			recon->set_num_subiterations(value);
		}
		else if (boost::iequals(name, "start_subiteration_num")) {
			if (value < 1)
				return wrongIntParameterValue
				("IterativeReconstruction::start_subiteration_num",
				value, __FILE__, __LINE__);
			recon->set_start_subiteration_num(value);
		}
		else if (boost::iequals(name, "subiteration_num")) {
			if (value < 1)
				return wrongIntParameterValue
				("IterativeReconstruction::subiteration_num",
				value, __FILE__, __LINE__);
			xSTIR_subiteration(recon) = value;
		}
		else if (boost::iequals(name, "save_interval")) {
			if (value < 1 || value > recon->get_num_subiterations())
				return wrongIntParameterValue
				("IterativeReconstruction::save_interval",
				value, __FILE__, __LINE__);
			recon->set_save_interval(value);
		}
		else if (boost::iequals(name, "inter_iteration_filter_interval")) {
			if (value < 0)
				return wrongIntParameterValue
				("IterativeReconstruction::inter_iteration_filter_interval",
				value, __FILE__, __LINE__);
			recon->set_inter_iteration_filter_interval(value);
		}
		else
			return parameterNotFound(name, __FILE__, __LINE__);
	}
	return new DataHandle;
}

void*
cSTIR_iterativeReconstructionParameter(const DataHandle* handle, std::string name)
{
	CAST_PTR(IterativeReconstruction<Image3DF>, recon, handle->data());
	if (boost::iequals(name, "num_subsets"))
		return intDataHandle(recon->get_num_subsets());
	if (boost::iequals(name, "start_subset_num"))
		return intDataHandle(recon->get_start_subset_num());
	if (boost::iequals(name, "num_subiterations"))
		return intDataHandle(recon->get_num_subiterations());
	if (boost::iequals(name, "start_subiteration_num"))
		return intDataHandle(recon->get_start_subiteration_num());
	if (boost::iequals(name, "subiteration_num"))
		return intDataHandle(xSTIR_subiteration(recon));
	if (boost::iequals(name, "objective_function")) {
		NEW(DataHandle, h);
		NEW(boost::shared_ptr<GeneralisedObjectiveFunction<Image3DF> >, sptr);
		*sptr = recon->get_objective_function_sptr();
		h->set((void*)sptr, 0);
		return (void*)h;
	}
	return parameterNotFound(name.c_str(), __FILE__, __LINE__);
}

void*
cSTIR_setOSMAPOSLParameter
(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(OSMAPOSLReconstruction<Image3DF>, recon, hp->data());
	if (boost::iequals(name, "MAP_model"))
		recon->set_MAP_model((char*)hv->data());
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void* 
cSTIR_OSMAPOSLParameter(const DataHandle* handle, std::string name)
{
	CAST_PTR(OSMAPOSLReconstruction<Image3DF>, recon, handle->data());
	return parameterNotFound(name.c_str(), __FILE__, __LINE__);
}

void*
cSTIR_setOSSPSParameter(DataHandle* hp, const char* name, const DataHandle* hv)
{
	CAST_PTR(xSTIR_OSSPSReconstruction3DF, recon, hp->data());
	if (boost::iequals(name, "relaxation_parameter"))
		recon->relaxation_parameter_value() = floatDataFromHandle(hv);
	else
		return parameterNotFound(name, __FILE__, __LINE__);
	return new DataHandle;
}

void* 
cSTIR_OSSPSParameter(const DataHandle* handle, std::string name)
{
	CAST_PTR(OSSPSReconstruction<Image3DF>, recon, handle->data());
	return parameterNotFound(name.c_str(), __FILE__, __LINE__);
}
