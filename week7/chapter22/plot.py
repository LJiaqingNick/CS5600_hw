import matplotlib.pyplot as plt
import os

VPN_MASK = 2**40 - 2**13
SHIFT = 13
POLICY = ["FIFO", "LRU", "OPT", "UNOPT", "RAND", "CLOCK"]
MAX_CACHE = 8

def convertToVPN(virtualAddress: str) -> int:
  hexNum = int(virtualAddress, 16)
  vpn = (hexNum & VPN_MASK) >> SHIFT
  return vpn

def main():
  data = open("data.txt", "r")
  vpns = []
  for line in data:
    if line[0] != "=":
      vpns.append(str(convertToVPN(line[3:11])))
  data.close()
  addresses = ",".join(vpns)
  caches = [cache for cache in range(1, MAX_CACHE)]
  hitRates = []
  for policy in POLICY:
    row = []
    for cache in caches:
      temp = os.popen(f"python3 paging-policy.py -C {cache} -N -c -p {policy} -a {addresses[:500]}")
      row.append(temp.read().split("\n")[11].split(' ')[-1])
    hitRates.append([float(rate) for rate in row])

  for i in range(len(POLICY)):
    plt.plot(caches, hitRates[i])
  plt.legend(POLICY)
  plt.xlabel("Cache Size")
  plt.ylabel("Hit rate")
  plt.show()

if __name__ == "__main__":
  main()