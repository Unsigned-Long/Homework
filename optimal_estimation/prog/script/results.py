import math

from plt_utils import drawer
from helper import get_array_fields
import matplotlib.pyplot as plt
from helper import get_array_fields
import json
from matplotlib.patches import Circle
from matplotlib.patheffects import withStroke
from mpl_toolkits.axes_grid1.anchored_artists import AnchoredSizeBar
from mpl_toolkits.axes_grid1.inset_locator import mark_inset, zoomed_inset_axes

obv_filename = '/home/csl/Homework/optimal_estimation/prog/data/observation.txt'
res_filename = '/home/csl/Homework/optimal_estimation/prog/data/results.json'

colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]


class State(object):
    def __init__(self, t, x, y, vx, vy, var_vec):
        self.t = t
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        self.var_vec = var_vec

    def __str__(self):
        return "{}, {}, {}, {}, {}, {}".format(self.t, self.x, self.y, self.vx, self.vy, self.var_vec)


def annotate(ax, x, y, r, text, code):
    # Circle marker
    royal_blue = [0, 20 / 256, 82 / 256]
    c = Circle((x, y), radius=r, clip_on=False, zorder=10, linewidth=2.5,
               edgecolor=royal_blue + [0.6], facecolor='none',
               path_effects=[withStroke(linewidth=7, foreground='white')])
    ax.add_artist(c)

    # use path_effects as a background for the texts
    # draw the path_effects and the colored text separately so that the
    # path_effects cannot clip other texts
    for path_effects in [[withStroke(linewidth=7, foreground='white')], []]:
        color = 'white' if path_effects else royal_blue
        ax.text(x, y - 1.5 * r, text, zorder=100,
                ha='center', va='top', weight='bold', color=color,
                style='italic', fontfamily='monospace',
                path_effects=path_effects)

        # color = 'white' if path_effects else 'black'
        # ax.text(x, y - 2.0 * r, code, zorder=100,
        #         ha='center', va='top', weight='normal', color=color,
        #         fontfamily='monospace', fontsize='medium',
        #         path_effects=path_effects)


def load_obv_data(filename):
    file = open(filename, "r")
    lines = file.readlines()
    data = []
    t = 0.1
    for line in lines:
        items = line.split(',')
        r = float(items[0])
        a = float(items[1])
        data.append([t, r * math.sin(a), r * math.cos(a)])
        t += 0.1

    return data


def load_results(filename, field):
    est_states = get_array_fields(filename, ['Recorder', field])
    data = []
    for elem in est_states:
        s = State(elem['timestamp'], elem['state']['r0c0'], elem['state']['r1c0'],
                  elem['state']['r2c0'], elem['state']['r3c0'], elem['var'])
        data.append(s)
    return data


def load_kalman_gain(filename, field):
    raw_data = get_array_fields(filename, ['Recorder', field])
    data = []
    for elem in raw_data:
        data.append([elem['first'], elem['second']])
    return data


def draw_plot(ax, x, y, color, label=None, alpha=0.9):
    # ax.plot(x, y, c=color, lw=6, label=label, alpha=alpha, marker='o', ms=8)
    ax.plot(x, y, c=color, lw=6, label=label, alpha=alpha)


def draw_scatter(ax, x, y, color, label=None):
    ax.scatter(x, y, c=color, label=label, alpha=0.6, s=80)


def add_arrow(ax, x, y, color):
    for i in range(len(x) - 1):
        ax.annotate("", xy=(x[i + 1], y[i + 1]), xytext=(x[i], y[i]),
                    arrowprops=dict(arrowstyle="->", color=color, alpha=0.4))


if __name__ == '__main__':
    drawer.set_fig_size(20.0, 10.0)

    fig = plt.figure()
    ax1 = plt.subplot2grid((4, 4), (0, 0), rowspan=4, colspan=2)
    ax2 = plt.subplot2grid((4, 4), (0, 2))
    ax3 = plt.subplot2grid((4, 4), (1, 2))
    ax4 = plt.subplot2grid((4, 4), (2, 2))
    ax5 = plt.subplot2grid((4, 4), (3, 2))

    ax6 = plt.subplot2grid((4, 4), (0, 3))
    ax7 = plt.subplot2grid((4, 4), (1, 3))
    ax8 = plt.subplot2grid((4, 4), (2, 3))
    ax9 = plt.subplot2grid((4, 4), (3, 3))

    obv_data = load_obv_data(obv_filename)
    est_data = load_results(res_filename, 'estStates')
    pre_data = load_results(res_filename, 'preStates')

    draw_scatter(
        ax1, [item[1] for item in obv_data], [item[2] for item in obv_data], color=colors[0],
        label='Measurements'
    )

    drawer.set_xticks(ax1, 0.0, 200.0, 5)
    drawer.set_yticks(ax1, 320.0, 550.0, 5)
    ax1.set_box_aspect((530.0 - 330.0) / 200.0)
    add_arrow(ax1, [item[1] for item in obv_data], [item[2] for item in obv_data], color=colors[0])

    ax1.plot([item.x for item in pre_data], [item.y for item in pre_data], color=colors[1],
             label='Predicted States', lw=6, alpha=0.7)
    ax1.plot([item.x for item in est_data], [item.y for item in est_data], color=colors[2],
             label='Estimated States', lw=6, alpha=0.7)
    # x states
    ax2.plot([item.t for item in est_data], [math.sqrt(item.var_vec['r0c0']) for item in est_data],
             color=colors[0], label='estimated', lw=3)
    ax2.plot([item.t for item in pre_data], [math.sqrt(item.var_vec['r0c0']) for item in pre_data],
             color=colors[1], label='predicted', lw=3)

    ax3.plot([item.t for item in est_data], [math.sqrt(item.var_vec['r1c1']) for item in est_data],
             color=colors[0], label='estimated', lw=3)
    ax3.plot([item.t for item in pre_data], [math.sqrt(item.var_vec['r1c1']) for item in pre_data],
             color=colors[1], label='predicted', lw=3)

    ax4.plot([item.t for item in est_data], [math.sqrt(item.var_vec['r2c2']) for item in est_data],
             color=colors[0], label='estimated', lw=3)
    ax4.plot([item.t for item in pre_data], [math.sqrt(item.var_vec['r2c2']) for item in pre_data],
             color=colors[1], label='predicted', lw=3)

    ax5.plot([item.t for item in est_data], [math.sqrt(item.var_vec['r3c3']) for item in est_data],
             color=colors[0], label='estimated', lw=3)
    ax5.plot([item.t for item in pre_data], [math.sqrt(item.var_vec['r3c3']) for item in pre_data],
             color=colors[1], label='predicted', lw=3)

    kxVec = load_kalman_gain(res_filename, 'kxVec')
    kyVec = load_kalman_gain(res_filename, 'kyVec')
    kvxVec = load_kalman_gain(res_filename, 'kvxVec')
    kvyVec = load_kalman_gain(res_filename, 'kvyVec')

    ax6.plot(
        [item[0] for item in kxVec], [item[1] for item in kxVec],
        color=colors[0], label='mes impact on ' + drawer.math_symbols('x'), lw=3
    )

    ax7.plot(
        [item[0] for item in kyVec], [item[1] for item in kyVec],
        color=colors[0], label='mes impact on ' + drawer.math_symbols('y'), lw=3
    )

    ax8.plot(
        [item[0] for item in kvxVec], [item[1] for item in kvxVec],
        color=colors[0], label='mes impact on ' + drawer.math_symbols('v_x'), lw=3
    )

    ax9.plot(
        [item[0] for item in kvyVec], [item[1] for item in kvyVec],
        color=colors[0], label='mes impact on ' + drawer.math_symbols('v_y'), lw=3
    )

    ax1.set_xlabel(drawer.math_symbols('x\;(m)'))
    ax1.set_ylabel(drawer.math_symbols('y\;(m)'))
    ax5.set_xlabel(drawer.math_symbols('t\;(s)'))
    ax9.set_xlabel(drawer.math_symbols('t\;(s)'))
    for elem in [ax1, ax2, ax3, ax4, ax5, ax6, ax7, ax8, ax9]:
        drawer.add_grids(elem)
        elem.legend()
        if elem != ax1:
            drawer.set_xticks(elem, 0.0, 10.0, 5)

    ax2.set_ylabel(drawer.math_symbols('\sigma_x'))
    ax3.set_ylabel(drawer.math_symbols('\sigma_y'))
    ax4.set_ylabel(drawer.math_symbols('\sigma_{v_x}'))
    ax5.set_ylabel(drawer.math_symbols('\sigma_{v_y}'))
    drawer.set_yticks(ax2, 0.0, 10.0, 2)
    drawer.set_yticks(ax3, 0.0, 10.0, 2)
    drawer.set_yticks(ax4, 0.0, 10.0, 2)
    drawer.set_yticks(ax5, 0.0, 10.0, 2)
    # drawer.show_figure('/home/csl/Homework/optimal_estimation/prog/img/local_kf_1.pdf')
    drawer.show_figure('/home/csl/Homework/optimal_estimation/prog/img/local_kf_2.pdf')
    # drawer.show_figure('/home/csl/Homework/optimal_estimation/prog/img/global_kf.pdf')
