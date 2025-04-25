from check import get_json, readFileToArray, mulMatrices, writeResult
from const import PATH


if __name__ == "__main__":
    path = get_json(PATH)

    matrixA_10_5 = readFileToArray(path["matrixA_10_5"])
    matrixB_10_5 = readFileToArray(path["matrixB_10_5"])
    resMatrix_10_5 = readFileToArray(path["resMatrix_10_5"])

    mul_10_5 = mulMatrices(matrixA_10_5, matrixB_10_5)

    writeResult(path["resultFile_5"], mul_10_5, resMatrix_10_5, 10, 10)

    matrixA_100_5 = readFileToArray(path["matrixA_100_5"])
    matrixB_100_5 = readFileToArray(path["matrixB_100_5"])
    resMatrix_100_5 = readFileToArray(path["resMatrix_100_5"])

    mul_100_5 = mulMatrices(matrixA_100_5, matrixB_100_5)

    writeResult(path["resultFile_5"], mul_100_5, resMatrix_100_5, 100, 100)

    matrixA_500_5 = readFileToArray(path["matrixA_500_5"])
    matrixB_500_5 = readFileToArray(path["matrixB_500_5"])
    resMatrix_500_5 = readFileToArray(path["resMatrix_500_5"])

    mul_500_5 = mulMatrices(matrixA_500_5, matrixB_500_5)

    writeResult(path["resultFile_5"], mul_500_5, resMatrix_500_5, 500, 500)

    matrixA_1000_5 = readFileToArray(path["matrixA_1000_5"])
    matrixB_1000_5 = readFileToArray(path["matrixB_1000_5"])
    resMatrix_1000_5 = readFileToArray(path["resMatrix_1000_5"])

    mul_1000_5 = mulMatrices(matrixA_1000_5, matrixB_1000_5)

    writeResult(path["resultFile_5"], mul_1000_5, resMatrix_1000_5, 1000, 1000)

    matrixA_2000_5 = readFileToArray(path["matrixA_2000_5"])
    matrixB_2000_5 = readFileToArray(path["matrixB_2000_5"])
    resMatrix_2000_5 = readFileToArray(path["resMatrix_2000_5"])

    mul_2000_5 = mulMatrices(matrixA_2000_5, matrixB_2000_5)

    writeResult(path["resultFile_5"], mul_2000_5, resMatrix_2000_5, 2000, 2000)

    matrixA_10_10 = readFileToArray(path["matrixA_10_10"])
    matrixB_10_10 = readFileToArray(path["matrixB_10_10"])
    resMatrix_10_10 = readFileToArray(path["resMatrix_10_10"])

    mul_10_10 = mulMatrices(matrixA_10_10, matrixB_10_10)

    writeResult(path["resultFile_10"], mul_10_10, resMatrix_10_10, 10, 10)

    matrixA_100_10 = readFileToArray(path["matrixA_100_10"])
    matrixB_100_10 = readFileToArray(path["matrixB_100_10"])
    resMatrix_100_10 = readFileToArray(path["resMatrix_100_10"])

    mul_100_10 = mulMatrices(matrixA_100_10, matrixB_100_10)

    writeResult(path["resultFile_10"], mul_100_10, resMatrix_100_10, 100, 100)

    matrixA_500_10 = readFileToArray(path["matrixA_500_10"])
    matrixB_500_10 = readFileToArray(path["matrixB_500_10"])
    resMatrix_500_10 = readFileToArray(path["resMatrix_500_10"])

    mul_500_10 = mulMatrices(matrixA_500_10, matrixB_500_10)

    writeResult(path["resultFile_10"], mul_500_10, resMatrix_500_10, 500, 500)

    matrixA_1000_10 = readFileToArray(path["matrixA_1000_10"])
    matrixB_1000_10 = readFileToArray(path["matrixB_1000_10"])
    resMatrix_1000_10 = readFileToArray(path["resMatrix_1000_10"])

    mul_1000_10 = mulMatrices(matrixA_1000_10, matrixB_1000_10)

    writeResult(path["resultFile_10"], mul_1000_10, resMatrix_1000_10, 1000, 1000)

    matrixA_2000_10 = readFileToArray(path["matrixA_2000_10"])
    matrixB_2000_10 = readFileToArray(path["matrixB_2000_10"])
    resMatrix_2000_10 = readFileToArray(path["resMatrix_2000_10"])

    mul_2000_10 = mulMatrices(matrixA_2000_10, matrixB_2000_10)

    writeResult(path["resultFile_10"], mul_2000_10, resMatrix_2000_10, 2000, 2000)

    matrixA_10_15 = readFileToArray(path["matrixA_10_15"])
    matrixB_10_15 = readFileToArray(path["matrixB_10_15"])
    resMatrix_10_15 = readFileToArray(path["resMatrix_10_15"])

    mul_10_15 = mulMatrices(matrixA_10_15, matrixB_10_15)

    writeResult(path["resultFile_15"], mul_10_15, resMatrix_10_15, 10, 10)

    matrixA_100_15 = readFileToArray(path["matrixA_100_15"])
    matrixB_100_15 = readFileToArray(path["matrixB_100_15"])
    resMatrix_100_15 = readFileToArray(path["resMatrix_100_15"])

    mul_100_15 = mulMatrices(matrixA_100_15, matrixB_100_15)

    writeResult(path["resultFile_15"], mul_100_15, resMatrix_100_15, 100, 100)

    matrixA_500_15 = readFileToArray(path["matrixA_500_15"])
    matrixB_500_15 = readFileToArray(path["matrixB_500_15"])
    resMatrix_500_15 = readFileToArray(path["resMatrix_500_15"])

    mul_500_15 = mulMatrices(matrixA_500_15, matrixB_500_15)

    writeResult(path["resultFile_15"], mul_500_15, resMatrix_500_15, 500, 500)

    matrixA_1000_15 = readFileToArray(path["matrixA_1000_15"])
    matrixB_1000_15 = readFileToArray(path["matrixB_1000_15"])
    resMatrix_1000_15 = readFileToArray(path["resMatrix_1000_15"])

    mul_1000_15 = mulMatrices(matrixA_1000_15, matrixB_1000_15)

    writeResult(path["resultFile_15"], mul_1000_15, resMatrix_1000_15, 1000, 1000)

    matrixA_2000_15 = readFileToArray(path["matrixA_2000_15"])
    matrixB_2000_15 = readFileToArray(path["matrixB_2000_15"])
    resMatrix_2000_15 = readFileToArray(path["resMatrix_2000_15"])

    mul_2000_15 = mulMatrices(matrixA_2000_15, matrixB_2000_15)

    writeResult(path["resultFile_15"], mul_2000_15, resMatrix_2000_15, 2000, 2000)

    matrixA_10_20 = readFileToArray(path["matrixA_10_20"])
    matrixB_10_20 = readFileToArray(path["matrixB_10_20"])
    resMatrix_10_20 = readFileToArray(path["resMatrix_10_20"])

    mul_10_20 = mulMatrices(matrixA_10_20, matrixB_10_20)

    writeResult(path["resultFile_20"], mul_10_20, resMatrix_10_20, 10, 10)

    matrixA_100_20 = readFileToArray(path["matrixA_100_20"])
    matrixB_100_20 = readFileToArray(path["matrixB_100_20"])
    resMatrix_100_20 = readFileToArray(path["resMatrix_100_20"])

    mul_100_20 = mulMatrices(matrixA_100_20, matrixB_100_20)

    writeResult(path["resultFile_20"], mul_100_20, resMatrix_100_20, 100, 100)

    matrixA_500_20 = readFileToArray(path["matrixA_500_20"])
    matrixB_500_20 = readFileToArray(path["matrixB_500_20"])
    resMatrix_500_20 = readFileToArray(path["resMatrix_500_20"])

    mul_500_20 = mulMatrices(matrixA_500_20, matrixB_500_20)

    writeResult(path["resultFile_20"], mul_500_20, resMatrix_500_20, 500, 500)

    matrixA_1000_20 = readFileToArray(path["matrixA_1000_20"])
    matrixB_1000_20 = readFileToArray(path["matrixB_1000_20"])
    resMatrix_1000_20 = readFileToArray(path["resMatrix_1000_20"])

    mul_1000_20 = mulMatrices(matrixA_1000_20, matrixB_1000_20)

    writeResult(path["resultFile_20"], mul_1000_20, resMatrix_1000_20, 1000, 1000)

    matrixA_2000_20 = readFileToArray(path["matrixA_2000_20"])
    matrixB_2000_20 = readFileToArray(path["matrixB_2000_20"])
    resMatrix_2000_20 = readFileToArray(path["resMatrix_2000_20"])

    mul_2000_20 = mulMatrices(matrixA_2000_20, matrixB_2000_20)

    writeResult(path["resultFile_20"], mul_2000_20, resMatrix_2000_20, 2000, 2000)
