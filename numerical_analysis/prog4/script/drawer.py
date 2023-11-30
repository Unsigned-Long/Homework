import csv
import math

from plt_utils import drawer
import matplotlib.pyplot as plt
import numpy as np

folder = '/home/csl/Homework/numerical_analysis/prog3/data/sinx/'

filenames = ['truth.txt', 'lagAvgSamples.txt', 'lagAvgResults.txt',
             'lagChebyshevSamples.txt', 'lagChebyshevResults.txt']

colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]


def load_data(filename):
    data = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            data.append([float(row[0]), float(row[1])])
    return data


def draw_truth(ax, data):
    ax.plot([elem[0] for elem in data], [elem[1] for elem in data],
            c=colors[2], lw=20, label='function truth', alpha=0.2)


def draw_sample(ax, data, label):
    ax.scatter(
        [elem[0] for elem in data], [elem[1] for elem in data], c=colors[1], s=150, label=label,
        zorder=1, marker='P'
    )


def draw_results(ax, data):
    ax.plot([elem[0] for elem in data], [elem[1] for elem in data], c=colors[3],
            lw=5, label='results', alpha=0.8, zorder=5)


if __name__ == '__main__':
    drawer.set_fig_size(25.0, 8.0)
    fig, axs = plt.subplots(1, 2, sharex=True, sharey=True)

    truth = load_data(folder + filenames[0])
    draw_truth(axs[0], truth)
    draw_truth(axs[1], truth)

    lagAvgSamples = load_data(folder + filenames[1])
    draw_sample(axs[0], lagAvgSamples, label="average samples")

    lagAvgResults = load_data(folder + filenames[2])
    draw_results(axs[0], lagAvgResults)

    lagChebyshevSamples = load_data(folder + filenames[3])
    draw_sample(axs[1], lagChebyshevSamples, label="chebyshev samples")

    lagChebyshevResults = load_data(folder + filenames[4])
    draw_results(axs[1], lagChebyshevResults)

    drawer.set_xticks(axs[0], -5.0, 5.0, 10)
    # drawer.set_yticks(axs[0], -0.3, 1.1, 7)
    drawer.set_yticks(axs[0], -1.2, 1.2, 6)
    # drawer.set_yticks(axs[0], -10.0, 170, 9)
    # drawer.set_yticks(axs[0], -2.0, 6, 8)
    # drawer.set_yticks(axs[0], -1.0, 6, 7)
    drawer.add_grids(axs[0])
    drawer.add_grids(axs[1])
    axs[0].set_title('Average Sampled Interpolation Points')
    axs[1].set_title('Chebyshev Sampled Interpolation Points')
    axs[0].legend()
    axs[1].legend()
    drawer.show_figure(folder + 'results30.pdf')
