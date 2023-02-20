#ifndef config_h
#define config_h

// define class name and unique id
#define MODEL_IDENTIFIER ExamplePart3
#define INSTANTIATION_TOKEN "{07f493df-5775-40d2-bd49-1a2b46323ced}"

#define CO_SIMULATION
#define MODEL_EXCHANGE

// define model size
#define NX 1
#define NZ 0

#define SET_FLOAT64

#define FIXED_SOLVER_STEP 0.1
#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_time, vr_x3, vr_x4, vr_der_x4
} ValueReference;

typedef struct {
    double x3;
    double x4;
    double der_x4;
} ModelData;

#endif /* config_h */
