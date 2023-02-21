""" This example demonstrates how to use the FMU.get*() and FMU.set*() functions
 to set custom input and control the simulation """

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
from fmpy.util import plot_result
import numpy as np
import shutil


def simulate_custom_input(show_plot=True):

    # define the model name and simulation parameters
    fmu_filename = 'build/fmus/ExamplePart3.fmu'
    # fmu_filename = 'MasterSimFMUs/tmp.fmu'
    start_time = 0.0
    stop_time = 6.0
    step_size = 0.1

    # read the model description
    model_description = read_model_description(fmu_filename)

    # collect the value references
    vrs = {}
    for variable in model_description.modelVariables:
        vrs[variable.name] = variable.valueReference

    # get the value references for the variables we want to get/set
    vr_x3   = vrs['x3']  
    vr_x4   = vrs['x4']  
    vr_der_x4   = vrs['der(x4)']  

    # extract the FMU
    unzipdir = extract(fmu_filename)
    fmu = FMU2Slave(guid=model_description.guid,
                    unzipDirectory=unzipdir,
                    modelIdentifier=model_description.coSimulation.modelIdentifier,
                    instanceName='instance1')

    # initialize
    fmu.instantiate()
    fmu.setupExperiment(startTime=start_time)
    fmu.enterInitializationMode()
    fmu.exitInitializationMode()

    time = start_time

    rows = []  # list to record the results

    # simulation loop
    while time < stop_time:

        # NOTE: the FMU.get*() and FMU.set*() functions take lists of
        # value references as arguments and return lists of values

        # set the input
        fmu.setReal([vr_x3], [0.0 if time < 2.0 or time > 4.0 else 1.0])
        input, output, derivative = fmu.getReal([vr_x3, vr_x4, vr_der_x4])

        # perform one step
        fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)

        # advance the time
        time += step_size

        # get the values
        input, output, derivative = fmu.getReal([vr_x3, vr_x4, vr_der_x4])

        # append the results
        rows.append((time, input, output))

    fmu.terminate()
    fmu.freeInstance()

    # clean up
    shutil.rmtree(unzipdir, ignore_errors=True)

    # convert the results to a structured NumPy array
    result = np.array(rows, dtype=np.dtype([('time', np.float64), ('x3', np.float64), ('x4', np.float64)]))

    # plot the results
    if show_plot:
        plot_result(result)

    return time

if __name__ == '__main__':

    simulate_custom_input()
