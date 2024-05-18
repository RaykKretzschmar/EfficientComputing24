import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Load the data from the output.csv file
data = pd.read_csv("pnorm.csv")
data.columns = ["type", "threads", "size", "p", "time"]

data["size"] = np.log10(data["size"])
data["time"] = np.log10(data["time"])

# Create a 3D axis object
fig = plt.figure(figsize=(8, 7))
ax1 = fig.add_subplot(311, projection="3d")
ax2 = fig.add_subplot(312, projection="3d")
ax3 = fig.add_subplot(313, projection="3d")

# seperate for each p
# p = 1
ax1.scatter(
    data[(data["type"] == "Serial") & (data["p"] == 1)]["size"],
    data[(data["type"] == "Serial") & (data["p"] == 1)]["threads"],
    data[(data["type"] == "Serial") & (data["p"] == 1)]["time"],
    c="b",
    label="Serial",
)

ax1.scatter(
    data[(data["type"] == "Parallel") & (data["p"] == 1)]["size"],
    data[(data["type"] == "Parallel") & (data["p"] == 1)]["threads"],
    data[(data["type"] == "Parallel") & (data["p"] == 1)]["time"],
    c="r",
    label="Parallel",
)

ax1.set_xlabel("Size (log10)")
ax1.set_ylabel("Number of Threads")
ax1.set_zlabel("Execution Time (log10)")
ax1.set_title("Comparison of Serial and Parallel Execution Times for p=1")
ax1.legend()

# p = 2
ax2.scatter(
    data[(data["type"] == "Serial") & (data["p"] == 2)]["size"],
    data[(data["type"] == "Serial") & (data["p"] == 2)]["threads"],
    data[(data["type"] == "Serial") & (data["p"] == 2)]["time"],
    c="b",
    label="Serial",
)

ax2.scatter(
    data[(data["type"] == "Parallel") & (data["p"] == 2)]["size"],
    data[(data["type"] == "Parallel") & (data["p"] == 2)]["threads"],
    data[(data["type"] == "Parallel") & (data["p"] == 2)]["time"],
    c="r",
    label="Parallel",
)

ax2.set_xlabel("Size (log10)")
ax2.set_ylabel("Number of Threads")
ax2.set_zlabel("Execution Time (log10)")
ax2.set_title("Comparison of Serial and Parallel Execution Times for p=2")
ax2.legend()

# p = INFINITY
ax3.scatter(
    data[(data["type"] == "Serial") & (data["p"] == np.inf)]["size"],
    data[(data["type"] == "Serial") & (data["p"] == np.inf)]["threads"],
    data[(data["type"] == "Serial") & (data["p"] == np.inf)]["time"],
    c="b",
    label="Serial",
)

ax3.scatter(
    data[(data["type"] == "Parallel") & (data["p"] == np.inf)]["size"],
    data[(data["type"] == "Parallel") & (data["p"] == np.inf)]["threads"],
    data[(data["type"] == "Parallel") & (data["p"] == np.inf)]["time"],
    c="r",
    label="Parallel",
)

ax3.set_xlabel("Size (log10)")
ax3.set_ylabel("Number of Threads")
ax3.set_zlabel("Execution Time (log10)")
ax3.set_title("Comparison of Serial and Parallel Execution Times for p=INFINITY")
ax3.legend()

# Show the plot
plt.show()
