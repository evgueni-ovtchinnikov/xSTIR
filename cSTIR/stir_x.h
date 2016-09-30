#ifndef EXTRA_STIR_TYPES
#define EXTRA_STIR_TYPES

#include "data_handle.h"
#include "cstir.h"
#include "stir.h"
#include "stir_p.h"

#define CATCH \
	catch (LocalisedException& se) {\
		ExecutionStatus status(se);\
		DataHandle* handle = new DataHandle;\
		handle->set(0, &status);\
		return (void*)handle;\
		}\
	catch (...) {\
		ExecutionStatus status("unhandled exception", __FILE__, __LINE__);\
		DataHandle* handle = new DataHandle;\
		handle->set(0, &status);\
		return (void*)handle;\
		}\

class xSTIR_IterativeReconstruction3DF :
	public IterativeReconstruction<Image3DF> {
public:
	bool post_process() {
		return post_processing();
	}
	Succeeded setup(sptrImage3DF const& image) {
		return set_up(image);
	}
	void update(Image3DF &image) {
		update_estimate(image);
		end_of_iteration_processing(image);
		subiteration_num++;
	}
	int& subiteration() {
		return subiteration_num;
	}
	int subiteration() const {
		return subiteration_num;
	}
	void set_initial_estimate_file(const char* filename) {
		initial_data_filename = filename;
	}
};

class xSTIR_OSSPSReconstruction3DF : public OSSPSReconstruction < Image3DF > {
public:
	float& relaxation_parameter_value() {
		return relaxation_parameter;
	}
};

class xSTIR_GeneralisedObjectiveFunction3DF :
	public GeneralisedObjectiveFunction<Image3DF> {
public:
	bool post_process() {
		return post_processing();
	}
};

class xSTIR_PoissonLogLikelihoodWithLinearModelForMeanAndProjData3DF :
	public PoissonLogLikelihoodWithLinearModelForMeanAndProjData<Image3DF> {
public:
	void set_input_file(const char* filename) {
		input_filename = filename;
	}
};

class xSTIR_GeneralisedPrior3DF : public GeneralisedPrior < Image3DF > {
public:
	bool post_process() {
		return post_processing();
	}
};

class xSTIR_QuadraticPrior3DF : public QuadraticPrior < float > {
public:
	void only2D(int only) {
		only_2D = only != 0;
	}
};

inline bool xSTIR_setupPrior(void* ptr)
{
	CAST_PTR(boost::shared_ptr< GeneralisedPrior<Image3DF> >, sptr_obj, ptr);
	CAST_PTR(xSTIR_GeneralisedPrior3DF, obj, sptr_obj->get());
	bool status = obj->post_process();
	return status;
}

inline bool xSTIR_setupObjectiveFunction(void* ptr)
{
	CAST_PTR(boost::shared_ptr< GeneralisedObjectiveFunction<Image3DF> >,
		sptr_obj, ptr);
	CAST_PTR(xSTIR_GeneralisedObjectiveFunction3DF, obj, sptr_obj->get());
	bool status = obj->post_process();
	return status;
}

inline Succeeded xSTIR_setupReconstruction(void* ptr, sptrImage3DF const& image)
{
	CAST_PTR(boost::shared_ptr<xSTIR_IterativeReconstruction3DF>, sptr, ptr);
	xSTIR_IterativeReconstruction3DF* recon = sptr->get();
	// not needed - default is non-zero string ("1") anyway
	//recon->set_initial_estimate_file("dummy.hv");
	Succeeded s = Succeeded::no;
	if (recon->post_process())
		return s;
	s = recon->setup(image);
	recon->subiteration() = recon->get_start_subiteration_num();
	return s;
}

inline void xSTIR_updateReconstruction(void* ptr, Image3DF& image) 
{
	CAST_PTR(boost::shared_ptr<xSTIR_IterativeReconstruction3DF>, sptr, ptr);
	xSTIR_IterativeReconstruction3DF* recon = sptr->get();
	recon->update(image);
}

inline int& xSTIR_subiteration(void* ptr) 
{
	CAST_PTR(xSTIR_IterativeReconstruction3DF, recon, ptr);
	return recon->subiteration();
}

inline void xSTIR_set_initial_estimate_file(void* ptr, const char* filename) 
{
	CAST_PTR(xSTIR_IterativeReconstruction3DF, recon, ptr);
	recon->set_initial_estimate_file(filename);
}

template<class Image>
class PETAcquisitionModel {
public:
	void set_projectors(boost::shared_ptr<ProjectorByBinPair> sptr_projectors)
	{
		sptr_projectors_ = sptr_projectors;
	}
	boost::shared_ptr<ProjectorByBinPair> projectors_sptr()
	{
		return sptr_projectors_;
	}
	virtual Succeeded set_up(
		boost::shared_ptr<ProjData> sptr_acq,
		boost::shared_ptr<Image> sptr_image)
	{
		Succeeded s = Succeeded::no;
		if (sptr_projectors_.get()) {
			s = sptr_projectors_->set_up
				(sptr_acq->get_proj_data_info_sptr(), sptr_image);
			sptr_acq_template_ = sptr_acq;
			sptr_image_template_ = sptr_image;
		}
		return s;
	}
	void set_background_term(boost::shared_ptr<ProjData> sptr)
	{
		sptr_background_ = sptr;
	}
	void set_additive_term(boost::shared_ptr<ProjData> sptr)
	{
		sptr_add_ = sptr;
	}
	boost::shared_ptr<ProjData> additive_term_sptr()
	{
		return sptr_add_;
	}
	void set_normalisation(boost::shared_ptr<BinNormalisation> sptr)
	{
		sptr_normalisation_ = sptr;
	}
	boost::shared_ptr<BinNormalisation> normalisation_sptr()
	{
		return sptr_normalisation_;
	}
	void set_normalisation(boost::shared_ptr<ProjData> sptr)
	{
		sptr_normalisation_.reset(new BinNormalisationFromProjData(sptr));
	}
	void cancel_background_term()
	{
		sptr_background_.reset();
	}
	void cancel_additive_term()
	{
		sptr_add_.reset();
	}
	void cancel_normalisation()
	{
		sptr_normalisation_.reset();
	}
	boost::shared_ptr<ProjData> forward(const Image& image, const char* file = 0)
	{
		boost::shared_ptr<ProjData> sptr_fd;

		if (file && strlen(file) > 0)
			sptr_fd.reset(
				new ProjDataInterfile(sptr_acq_template_->get_exam_info_sptr(),
				sptr_acq_template_->get_proj_data_info_sptr(), file));
		else
			sptr_fd.reset(
			new ProjDataInMemory(sptr_acq_template_->get_exam_info_sptr(),
			sptr_acq_template_->get_proj_data_info_sptr()));

		sptr_projectors_->get_forward_projector_sptr()->forward_project
			(*sptr_fd, image);
		if (file && strlen(file) > 0) {
			sptr_fd.reset();
			sptr_fd = ProjData::read_from_file(file);
		}

		if (sptr_add_.get()) {
			add_(sptr_fd, sptr_add_);
			std::cout << "additive term added\n";
		}
		else
			std::cout << "no additive term added\n";

		if (sptr_normalisation_.get() && !sptr_normalisation_->is_trivial()) {
			sptr_normalisation_->undo(*sptr_fd, 0, 1);
			//sptr_normalisation_->apply(*sptr_fd, 0, 1);
			std::cout << "normalisation applied\n";
		}
		else
			std::cout << "no normalisation applied\n";

		if (sptr_background_.get()) {
			add_(sptr_fd, sptr_background_);
			std::cout << "background term added\n";
		}
		else
			std::cout << "no background term added\n";
		return sptr_fd;
	}

	boost::shared_ptr<Image> backward(const ProjData& ad)
	{
		ProjDataInMemory adc(ad.get_exam_info_sptr(), ad.get_proj_data_info_sptr());
		adc.fill(ad);

		if (sptr_normalisation_.get()) {
			std::cout << "applying normalisation...\n";
			sptr_normalisation_->undo(adc, 0, 1);
		}

		boost::shared_ptr<Image> sptr_im(sptr_image_template_->clone());
		sptr_projectors_->get_back_projector_sptr()->back_project
			(*sptr_im, adc);
		return sptr_im;
	}

protected:
	boost::shared_ptr<ProjectorByBinPair> sptr_projectors_;
	boost::shared_ptr<ProjData> sptr_acq_template_;
	boost::shared_ptr<Image> sptr_image_template_;
	boost::shared_ptr<ProjData> sptr_add_;
	boost::shared_ptr<ProjData> sptr_background_;
	boost::shared_ptr<BinNormalisation> sptr_normalisation_;

private:
	void add_
		(boost::shared_ptr<ProjData> sptr_a, boost::shared_ptr<ProjData> sptr_b)
	{
		size_t size_a = sptr_a->size_all();
		size_t size_b = sptr_b->size_all();
		if (size_a != size_b) {
			std::cout << "ERROR: mismatching sizes " << size_a
				<< " and " << size_b << ", skipping\n";
			return;
		}
		double* data_a = new double[size_a];
		double* data_b = new double[size_b];
		sptr_a->copy_to(data_a);
		sptr_b->copy_to(data_b);
		add_(size_a, data_a, data_b);
		sptr_a->fill_from(data_a);
		delete[] data_a;
		delete[] data_b;
	}
	void add_(size_t n, double* u, double* v)
	{
		for (size_t i = 0; i < n; i++)
			u[i] += v[i];
	}
};

template<class Image>
class PETAcquisitionModelUsingMatrix : public PETAcquisitionModel<Image> {
public:
	PETAcquisitionModelUsingMatrix()
	{
		this->sptr_projectors_.reset(new ProjectorPairUsingMatrix);
	}
	void set_matrix(boost::shared_ptr<ProjMatrixByBin> sptr_matrix)
	{
		sptr_matrix_ = sptr_matrix;
		((ProjectorPairUsingMatrix*)this->sptr_projectors_.get())->
			set_proj_matrix_sptr(sptr_matrix);
	}
	boost::shared_ptr<ProjMatrixByBin> matrix_sptr()
	{
		return ((ProjectorPairUsingMatrix*)this->sptr_projectors_.get())->
			get_proj_matrix_sptr();
	}
	virtual Succeeded set_up(
		boost::shared_ptr<ProjData> sptr_acq,
		boost::shared_ptr<Image> sptr_image)
	{
		if (!sptr_matrix_.get())
			return Succeeded::no;
		return PETAcquisitionModel<Image>::set_up(sptr_acq, sptr_image);
	}

private:
	boost::shared_ptr<ProjMatrixByBin> sptr_matrix_;
};

typedef PETAcquisitionModel<Image3DF> AcqMod3DF;
typedef PETAcquisitionModelUsingMatrix<Image3DF> AcqModUsingMatrix3DF;
typedef boost::shared_ptr<AcqMod3DF> sptrAcqMod3DF;

#endif