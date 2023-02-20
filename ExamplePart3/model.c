#include "config.h"
#include "model.h"

void setStartValues(ModelInstance *comp) {
    M(x3) = 0;
}

Status calculateValues(ModelInstance *comp) {
    M(der_x4) = M(x3);
    return OK;
}

Status getFloat64(ModelInstance* comp, ValueReference vr, double values[], size_t nValues, size_t* index) {

    calculateValues(comp);

    ASSERT_NVALUES(1);

    switch (vr) {
        case vr_time:
            values[(*index)++] = comp->time;
            return OK;
        case vr_x3:
            values[(*index)++] = M(x3);
            return OK;
        case vr_x4:
            values[(*index)++] = M(x4);
            return OK;
        case vr_der_x4:
            values[(*index)++] = M(der_x4);
            return OK;
        default:
            logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

Status setFloat64(ModelInstance* comp, ValueReference vr, const double values[], size_t nValues, size_t* index) {

    ASSERT_NVALUES(1);

    switch (vr) {
        case vr_x3:
            M(x3) = values[(*index)++];
            return OK;
        case vr_x4:
            M(x4) = values[(*index)++];
            return OK;
        case vr_der_x4:
            M(der_x4) = values[(*index)++];
            return OK;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

void getContinuousStates(ModelInstance *comp, double x[], size_t nx) {
    UNUSED(nx);
    x[0] = M(x4);
}

void setContinuousStates(ModelInstance *comp, const double x[], size_t nx) {
    UNUSED(nx);
    M(x4) = x[0];
}

void getDerivatives(ModelInstance *comp, double dx[], size_t nx) {
    UNUSED(nx);
    calculateValues(comp);
    dx[0] = M(der_x4);
}
