import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Load the data from the output.csv file
data = pd.read_csv("output.csv")
data.columns = ["type", "size", "threads", "time"]

data["size"] = np.log10(data["size"])
data["time"] = np.log10(data["time"])

# Create a 3D axis object
fig = plt.figure(figsize=(8, 7))
ax = fig.add_subplot(111, projection="3d")

# Plot serial data
ax.scatter(
    data[data["type"] == "Serial"]["size"],
    data[data["type"] == "Serial"]["threads"],
    data[data["type"] == "Serial"]["time"],
    c="b",
    label="Serial",
)

# Plot parallel data
ax.scatter(
    data[data["type"] == "Parallel"]["size"],
    data[data["type"] == "Parallel"]["threads"],
    data[data["type"] == "Parallel"]["time"],
    c="r",
    label="Parallel",
)

# Set axis labels and title
ax.set_xlabel("Size (log10)")
ax.set_ylabel("Number of Threads")
ax.set_zlabel("Execution Time (log10)")
ax.set_title("Comparison of Serial and Parallel Execution Times")

# Add a legend
ax.legend()

# Show the plot
plt.show()
