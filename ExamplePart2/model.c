#include "config.h"
#include "model.h"

void setStartValues(ModelInstance *comp) {
    M(x1) = 0;
    M(x2) = 0;
    M(x4) = 0;
}

Status calculateValues(ModelInstance *comp) {
    if(M(x1) == 1 && M(x2) < 0.01 && M(x4) < 2.5) {
        M(x3) = 3.0;
    }
    else if (M(x1) < 0.001 && M(x2) > 0 && M(x4) > -2.5){
        M(x3) = -3.0;
    }
    else {
        M(x3) = 0.0;
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
        case vr_x3:
            values[(*index)++] = M(x3);
            return OK;
        case vr_x4:
            values[(*index)++] = M(x4);
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
        case vr_x3:
            M(x3) = values[(*index)++];
            return OK;
        case vr_x4:
            M(x4) = values[(*index)++];
            return OK;
        default:
            logError(comp, "Set Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

