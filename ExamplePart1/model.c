#include "config.h"
#include "model.h"

void setStartValues(ModelInstance *comp) {
    M(x1) = 0;
    M(x2) = 0;
}

Status calculateValues(ModelInstance *comp) {
    if(comp->time < 1 || (comp->time > 2 && comp->time < 5)) {
        M(x1) = 0.0;
    }
    else {
        M(x1) = 1.0;
    }
    if(comp->time < 3 || (comp->time > 4 && comp->time < 6)) {
        M(x1) = 0.0;
    }
    else {
        M(x1) = 1.0;
    }
    return OK;
}

Status getFloat64(ModelInstance* comp, ValueReference vr, double values[], size_t nValues, size_t* index) {

    calculateValues(comp);

    ASSERT_NVALUES(1);

    switch (vr) {
        case vr_time:
            values[(*index)++] = comp->time;
            return OK;
        case vr_x1:
            values[(*index)++] = M(x1);
            return OK;
        case vr_x2:
            values[(*index)++] = M(x2);
            return OK;
        default:
            logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

Status setFloat64(ModelInstance* comp, ValueReference vr, const double values[], size_t nValues, size_t* index) {

    ASSERT_NVALUES(1);

    switch (vr) {
        case vr_x1:
            M(x1) = values[(*index)++];
            return OK;
        case vr_x2:
            M(x2) = values[(*index)++];
            return OK;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

void getContinuousStates(ModelInstance *comp, double x[], size_t nx) {
    UNUSED(nx);
    x[0] = M(x1);
    x[1] = M(x2)
}

void setContinuousStates(ModelInstance *comp, const double x[], size_t nx) {
    UNUSED(nx);
    M(x1) = x[0];
    M(x2) = x[1]
}