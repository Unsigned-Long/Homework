from plt_utils import drawer
import matplotlib.pyplot as plt
import numpy as np

filename = '/home/csl/Homework/numerical_analysis/prog1/data/step_length_cg.txt'

colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]


def load_update(filename):
    file = open(filename, "r")
    lines = file.readlines()
    return [float(item) for item in lines]


if __name__ == '__main__':
    drawer.set_fig_size(15.0, 5.0)
    fig, ax = plt.subplots(1, 1)
    data = load_update(filename)
    ax.plot(
        data[:50], c=colors[0], lw=4, marker='o',
        mfc=colors[0], ms=10, label='update'
    )
    ax.legend()
    drawer.set_xticks(ax, 0.0, 50.0, 10)
    ax.set_xlabel("Iterations")
    ax.set_ylabel('Update')
    drawer.set_yticks(ax, 0.0, 600.0, 3)
    drawer.add_grids(ax)
    drawer.show_figure('/home/csl/Homework/numerical_analysis/prog1/img/updates_cg.pdf')
