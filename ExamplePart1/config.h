#ifndef config_h
#define config_h

// define class name and unique id
#define MODEL_IDENTIFIER ExamplePart1
#define INSTANTIATION_TOKEN "{8615498b-60dc-43de-bea7-d200ce2bb32f}"

#define CO_SIMULATION
#define MODEL_EXCHANGE

// define model size
#define NX 1
#define NZ 0

#define SET_FLOAT64

#define FIXED_SOLVER_STEP 0.1
#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_time, vr_x1, vr_x2
} ValueReference;

typedef struct {
    double x1;
    double x2;
} ModelData;

#endif /* config_h */
