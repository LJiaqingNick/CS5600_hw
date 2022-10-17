import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def isFloat(number):
  try:
    float(number)
    return True
  except ValueError:
    return False

def main():
  file = open("data.txt", "r")
  x = []
  y = []
  for line in file:
    numbers = []
    for word in line.split():
      if isFloat(word):
        numbers.append(float(word))
    x.append(numbers[1])
    y.append(numbers[0])
  file.close()

  plt.title("Measure TLB")
  plt.xlabel("Numbe Of pages")
  plt.ylabel("Time PerAccess(ns)")
  plt.xscale("log")
  plt.plot(x, y, color="orange", marker='.', markersize=10)
  plt.show()

if __name__ == "__main__":
  main()