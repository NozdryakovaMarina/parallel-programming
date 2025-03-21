import numpy as np
import json

from typing import Dict


def get_json(falename: str) -> Dict[str, str]:
    """
    The function is for reading .json file

    Parameters: 
            name: path .json file

    Returns:
            data: key dictionary
    """
    try:
        with open(falename, "r") as file:
            data = json.load(file)
        return data
    except FileNotFoundError:
        print("The file was not found.")
        return None  
    except Exception as e:
        print(f"An error occurred while reading the JSON file: {str(e)}.")
        return None  


def readFileToArray(filename: str) -> np.ndarray:
    """
    The function reads the contents of the file and loads it into a NumPy array

    Parameters: 
            filename: path to the file containing the data that needs to be uploaded

    Returns: 
            np.ndarray: NumPy array containing data from a file. The data is loaded in integer format
    """
    return np.genfromtxt(filename, dtype=int)


def mulMatrices(matrixA: np.ndarray, matrixB: np.ndarray) -> np.ndarray:
    """
    The function Multiplies two matrices

    Parameters: 
            matrixA: first matrix for multiplication
    
            matrixB: second matrix is for multiplication

    Returns: 
            np.ndarray: result of multiplying two matrices
    """
    return np.dot(matrixA, matrixB)


def writeResult(filename: str, mulMatrix: np.ndarray, resMatrix: np.ndarray, rows: int, cols: int) -> None:
    """
    The function writes the results of the matrix match check to a file

    Parameters:
            filename: path to the file where the result will be written
    
            mulMatrix: produced matrix resulting from the multiplication
    
            res Matrix: matrix that the match is checked against
    
            rows: number of rows in the resulting matrix
    
            cols: number of columns in the resulting matrix
    """
    result = "Result matched" if np.array_equal(mulMatrix, resMatrix) else "Result didn't match("
    with open(filename, "a") as file:
        file.write(f"Size matrix: {rows}x{cols} | {result}\n")
