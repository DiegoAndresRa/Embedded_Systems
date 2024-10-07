import matplotlib.pyplot as plt
import random
import numpy as np
import sys
import os


def read_data(file):
    with open(file, "r") as f:
        data = [int(linea.strip()) for linea in f if linea.strip()]
    return data


def generate_hist(datasets, name_of_img, bins=20):
    colors = ["blue", "green", "orange", "purple", "red", "black"]

    plt.figure(figsize=(10, 6))

    for data in datasets:
        idx = random.randint(0, 5)
        # histogram
        plt.hist(
            datasets[data],
            bins=bins,
            color=colors[idx],
            edgecolor="black",
            density=True,
            alpha=0.6,
            label=data,
        )

        mu, std = np.mean(datasets[data]), np.std(datasets[data])
        x = np.linspace(min(datasets[data]) - 1, max(datasets[data]) + 1, 100)
        p = (1 / (std * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x - mu) / std) ** 2)

        # Graficar la curva de Gauss
        plt.plot(x, p, color=colors[idx], linewidth=2)

    plt.title("Histograms and Gauss")
    plt.xlabel("Nanoseconds")
    plt.ylabel("Frequency")
    plt.legend()

    # plt.xlim(101000000, 104500000) # from C to Python
    # plt.xlim(35000000, 62000000) # to Bash
    plt.ticklabel_format(style="scientific", axis="x", scilimits=(0, 0))
    plt.ticklabel_format(style="plain", axis="y")

    plt.savefig(f"Histograms/Histogram{name_of_img}.png", format="png")
    plt.close()


if __name__ == "__main__":

    if len(sys.argv) == 1:
        sys.exit(f"Error:\nUsage: {sys.argv[0]} data_file1 [data_file2 ... ]")
    elif len(sys.argv) == 2:
        name_of_img = os.path.basename(sys.argv[1]).split(".")[0]
    else:
        name_of_img = ""

    os.makedirs("Histograms", exist_ok=True)
    datasets = {}

    for arg in sys.argv[1:]:
        data = read_data(arg)
        name = os.path.basename(arg).split(".")[0]
        datasets[name] = data

    generate_hist(datasets, name_of_img, bins=20)
