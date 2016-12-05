#ifndef XSTIR_TESTS
#define XSTIR_TESTS

#define CAST_REF(T, X, Y) T& X = (T&)Y

#define OBJECT(Base, Obj, X, sptr_X) \
	boost::shared_ptr< Base > sptr_X(new Obj); Obj& X = (Obj&)*sptr_X

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

double diff(size_t n, double* u, double*v);
double dot(size_t n, double* u, double*v);
void test1();
void test2();
void test3();

#endif
