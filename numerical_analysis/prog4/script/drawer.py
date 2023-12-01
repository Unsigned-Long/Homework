import csv
import math

from plt_utils import drawer
import matplotlib.pyplot as plt
import numpy as np

colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]


def draw_func1():
    filename = '/home/csl/Homework/numerical_analysis/prog4/data/func1.pdf'
    drawer.set_fig_size(15.0, 8.0)
    fig, axs = plt.subplots(1, 1, sharex=True, sharey=True)

    x = np.arange(-5.0, 5.0, 0.01)
    y = 1 / (1 + x ** 2)

    axs.plot(x, y, c=colors[0], lw=5, label=drawer.math_symbols(r'f(x)=\frac{1}{1+x^2}'), alpha=0.8)
    axs.fill_between(
        x, y, where=(x > -2.0) & (x < 2.0), facecolor=colors[2],
        alpha=0.3, label=drawer.math_symbols('\int_{-2}^{2}f(x)dx=2.214...')
    )
    drawer.set_xticks(axs, -5.0, 5.0, 10)
    drawer.set_yticks(axs, 0.0, 1.2, 5)
    axs.set_xlabel(drawer.math_symbols('x'))
    axs.set_ylabel(drawer.math_symbols('f(x)'))

    drawer.add_grids(axs)
    axs.legend()
    drawer.show_figure(filename)


def draw_func2():
    filename = '/home/csl/Homework/numerical_analysis/prog4/data/func2.pdf'
    drawer.set_fig_size(15.0, 8.0)
    fig, axs = plt.subplots(1, 1, sharex=True, sharey=True)

    x = np.arange(-5.0, 15.0, 0.01)
    y = 0.1 * x ** 2 * (np.sin(np.pi * x)) ** 2

    axs.plot(
        x, y, c=colors[0], lw=5,
        label=drawer.math_symbols(r'f(x)=\frac{1}{10}\times x^2\times \sin^2 (\pi x)'), alpha=0.8)
    axs.fill_between(
        x, y, where=(x > 0.0) & (x < 10.0), facecolor=colors[2],
        alpha=0.3, label=drawer.math_symbols('\int_{0}^{10}f(x)dx=16.641...')
    )
    drawer.set_xticks(axs, -5.0, 15.0, 10)
    drawer.set_yticks(axs, 0.0, 25, 5)
    axs.set_xlabel(drawer.math_symbols('x'))
    axs.set_ylabel(drawer.math_symbols('f(x)'))

    drawer.add_grids(axs)
    axs.legend()
    drawer.show_figure(filename)


if __name__ == '__main__':
    # draw_func1()
    draw_func2()
