#ifndef config_h
#define config_h

// define class name and unique id
#define MODEL_IDENTIFIER ExamplePart2
#define INSTANTIATION_TOKEN "{b8c3f344-7e32-4783-b8ec-cc021e8a785f}"

#define CO_SIMULATION
#define MODEL_EXCHANGE

// define model size
#define NX 3
#define NZ 0

#define SET_FLOAT64

#define FIXED_SOLVER_STEP 0.1
#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_time, vr_x1, vr_x2, vr_x3, vr_x4
} ValueReference;

typedef struct {
    double x1;
    double x2;
    double x3;
    double x4;
} ModelData;

#endif /* config_h */
