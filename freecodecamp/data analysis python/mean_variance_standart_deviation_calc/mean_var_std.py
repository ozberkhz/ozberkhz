import numpy as np

def calculate(list):

    if len(list) < 9:
        raise ValueError("List must contain nine numbers.")

    v1 = np.array(list[0:3])
    v2 = np.array(list[3:6])
    v3 = np.array(list[6:9])
    
    matrix = np.vstack([v1,v2,v3])
    
    calculations = {
    'mean': [np.mean(matrix, axis = 0).tolist(), np.mean(matrix, axis = 1).tolist(), np.mean(matrix.flatten()).tolist()],
    'variance': [np.var(matrix, axis = 0).tolist(), np.var(matrix, axis = 1).tolist(), np.var(matrix.flatten()).tolist()],
    'standard deviation': [np.std(matrix, axis = 0).tolist(), np.std(matrix, axis = 1).tolist(), np.std(matrix.flatten()).tolist()],
    'max': [np.max(matrix, axis = 0).tolist(), np.max(matrix, axis = 1).tolist(), np.max(matrix.flatten()).tolist()],
    'min': [np.min(matrix, axis = 0).tolist(), np.min(matrix, axis = 1).tolist(), np.min(matrix.flatten()).tolist()],
    'sum': [np.sum(matrix, axis = 0).tolist(), np.sum(matrix, axis = 1).tolist(), np.sum(matrix.flatten()).tolist()]
    }
    print(calculations)
    return calculations
    
calculate([0, 1, 2, 3, 4, 5, 6, 754, 8])