from plt_utils import drawer
import matplotlib.pyplot as plt
import numpy as np

# steps = [
#     -2.00000, -2.00000,
#     0.08000, -0.61333,
#     1.00444, -2.00000,
#     1.52213, -1.65487,
#     1.75222, -2.00000,
#     1.88106, -1.91410,
#     1.93833, -2.00000,
#     1.97040, -1.97862,
#     1.98465, -2.00000,
#     1.99263, -1.99468,
#     1.99618, -2.00000,
#     1.99817, -1.99868,
#     1.99905, -2.00000,
#     1.99954, -1.99967,
#     1.99976, -2.00000,
#     1.99989, -1.99992,
#     1.99994, -2.00000,
#     1.99997, -1.99998,
#     1.99999, -2.00000,
#     1.99999, -1.99999,
#     2.00000, -2.00000,
# ]

steps = [
    5.00000, 2.00000,
    2.56675, -2.29397,
    2.01431, -1.98092,
    2.00270, -2.00140,
    2.00007, -1.99991,
    2.00001, -2.00001,
    2.00000, -2.00000,
]
colors = [
    '#ee1d23', '#3b4ba8', '#231f20', '#b935a2'
]

if __name__ == '__main__':
    drawer.set_fig_size(10.0, 10.0)
    fig, ax = plt.subplots(1, 1)
    delta = 0.25
    x = np.arange(-4.0, 6.0, delta)
    y = np.arange(-6.0, 4.0, delta)
    X, Y = np.meshgrid(x, y)
    Z = 1.5 * X * X + 2.0 * X * Y + 3.0 * Y * Y - 2.0 * X + 8.0 * Y
    CS = ax.contour(X, Y, Z, 8, linewidths=4, alpha=0.7, cmap='Greys_r')
    ax.plot(
        steps[::2], steps[1::2], c=colors[0], lw=4, marker='o',
        mfc=colors[1], ms=6, label='trajectory'
    )

    ax.clabel(CS, inline=True, fontsize=20)
    ax.set_title('Steepest Descent')
    ax.set_box_aspect(1)
    ax.set_xlabel(drawer.math_symbols('x_1'))
    ax.set_ylabel(drawer.math_symbols('x_2'))
    ax.legend()
    drawer.set_xticks(ax, -4, 6, 10)
    drawer.set_yticks(ax, -6, 4, 10)
    drawer.add_grids(ax)
    drawer.show_figure('/home/csl/Homework/numerical_analysis/prog1/img/steep_desc_2.pdf')
