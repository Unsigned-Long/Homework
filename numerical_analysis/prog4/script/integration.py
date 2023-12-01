import csv
import math

from plt_utils import drawer
import matplotlib.pyplot as plt
import numpy as np

save_filename = '/home/csl/Homework/numerical_analysis/prog4/data/func1_integration.pdf'


# save_filename = '/home/csl/Homework/numerical_analysis/prog4/data/func2_integration.pdf'


def func(x):
    return (1 / 6.0) * (x ** 3) - (1.0 / (4.0 * math.pi)) * (x ** 2) * math.sin(2 * math.pi * x) - (
            1.0 / (4 * math.pi * math.pi)) * x * math.cos(2 * math.pi * x) + (
            1.0 / (8.0 * math.pi * math.pi * math.pi)) * math.sin(2.0 * math.pi * x)


ground_truth = 2 * math.atan(2)
# ground_truth = 0.1 * (func(10.0) - func(0.0))
# ymin1 = 0.0
# ymax1 = 25.0
# ymin2 = 0.0
# ymax2 = 20.0

ymin1 = 0.0
ymax1 = 3.0
ymin2 = 0.0
ymax2 = 1.5

colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]

filenames = [
    '/home/csl/Homework/numerical_analysis/prog4/data/runge/trap.txt',
    '/home/csl/Homework/numerical_analysis/prog4/data/runge/simpson.txt',
    '/home/csl/Homework/numerical_analysis/prog4/data/runge/romberg.txt',
    # '/home/csl/Homework/numerical_analysis/prog4/data/zigzag/trap.txt',
    # '/home/csl/Homework/numerical_analysis/prog4/data/zigzag/simpson.txt',
    # '/home/csl/Homework/numerical_analysis/prog4/data/zigzag/romberg.txt'
]


def load_data(filename):
    data = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            data.append([float(row[0]), float(row[1])])
    return data


def draw_plot(axs, data, label, color):
    axs.plot([elem[0] for elem in data], [elem[1] for elem in data], c=color, lw=2,
             marker='o', ms=10, label=label, alpha=0.8)


def draw_error(ax, data, label, color, truth):
    error = np.array([elem[1] for elem in data]) - truth
    ax.plot([elem[0] for elem in data], np.abs(error), c=color, lw=2, marker='o', ms=10, label=label, alpha=0.8)


if __name__ == '__main__':
    drawer.set_fig_size(16.0, 8.0)
    fig, axs = plt.subplots(1, 2, sharex=True)

    trap_data = load_data(filenames[0])
    draw_plot(axs[0], trap_data, label='TrapezoidalComp', color=colors[0])
    draw_error(axs[1], trap_data, label='TrapezoidalComp', color=colors[0], truth=ground_truth)

    simpson_data = load_data(filenames[1])
    draw_plot(axs[0], simpson_data, label='SimpsonComp', color=colors[1])
    draw_error(axs[1], simpson_data, label='SimpsonComp', color=colors[1], truth=ground_truth)

    romberg_data = load_data(filenames[2])
    draw_plot(axs[0], romberg_data, label='Romberg', color=colors[2])
    draw_error(axs[1], romberg_data, label='Romberg', color=colors[2], truth=ground_truth)

    drawer.set_xticks(axs[0], 0.0, 10.0, 5)
    drawer.set_yticks(axs[0], ymin1, ymax1, 5)
    drawer.set_yticks(axs[1], ymin2, ymax2, 5)

    axs[0].axhline(y=ground_truth, color=colors[3], linestyle='-', lw=10, alpha=0.2, label='truth')

    drawer.add_grids(axs[0])
    drawer.add_grids(axs[1])
    axs[0].legend()
    axs[1].legend()
    axs[0].set_xlabel(drawer.math_symbols('n(trap,simpson)\mid k(romberg)'))
    axs[1].set_xlabel(drawer.math_symbols('n(trap,simpson)\mid k(romberg)'))
    axs[0].set_ylabel(drawer.math_symbols('integration'))
    axs[1].set_ylabel(drawer.math_symbols('error'))
    drawer.show_figure(save_filename)
