from check import get_json, readFileToArray, mulMatrices, writeResult
from const import PATH


if __name__ == "__main__":
    path = get_json(PATH)

    matrixA_10 = readFileToArray(path["matrixA_10"])
    matrixB_10 = readFileToArray(path["matrixB_10"])
    resMatrix_10 = readFileToArray(path["resMatrix_10"])

    mul_10 = mulMatrices(matrixA_10, matrixB_10)

    writeResult(path["resultFile"], mul_10, resMatrix_10, 10, 10)

    matrixA_100 = readFileToArray(path["matrixA_100"])
    matrixB_100 = readFileToArray(path["matrixB_100"])
    resMatrix_100 = readFileToArray(path["resMatrix_100"])

    mul_100 = mulMatrices(matrixA_100, matrixB_100)

    writeResult(path["resultFile"], mul_100, resMatrix_100, 100, 100)

    matrixA_500 = readFileToArray(path["matrixA_500"])
    matrixB_500 = readFileToArray(path["matrixB_500"])
    resMatrix_500 = readFileToArray(path["resMatrix_500"])

    mul_500 = mulMatrices(matrixA_500, matrixB_500)

    writeResult(path["resultFile"], mul_500, resMatrix_500, 500, 500)

    matrixA_1000 = readFileToArray(path["matrixA_1000"])
    matrixB_1000 = readFileToArray(path["matrixB_1000"])
    resMatrix_1000 = readFileToArray(path["resMatrix_1000"])

    mul_1000 = mulMatrices(matrixA_1000, matrixB_1000)

    writeResult(path["resultFile"], mul_1000, resMatrix_1000, 1000, 1000)

    matrixA_2000 = readFileToArray(path["matrixA_2000"])
    matrixB_2000 = readFileToArray(path["matrixB_2000"])
    resMatrix_2000 = readFileToArray(path["resMatrix_2000"])

    mul_2000 = mulMatrices(matrixA_2000, matrixB_2000)

    writeResult(path["resultFile"], mul_2000, resMatrix_2000, 2000, 2000)
  