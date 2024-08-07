import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import matplotlib
matplotlib.use('TkAgg')

# 线性回归并绘图的函数
def linear_regression_and_plot(x, y, pulses_x, pulses_y):
    # 拟合 X 坐标与 X 方向脉冲数的关系
    model_x = LinearRegression()
    model_x.fit(pulses_x.reshape(-1, 1), x)
    x_pred = model_x.predict(pulses_x.reshape(-1, 1))

    # 拟合 Y 坐标与 Y 方向脉冲数的关系
    model_y = LinearRegression()
    model_y.fit(pulses_y.reshape(-1, 1), y)
    y_pred = model_y.predict(pulses_y.reshape(-1, 1))

    # 绘制 X 坐标与 X 方向脉冲数的拟合曲线
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    plt.scatter(pulses_x, x, color='blue', label='Actual X')
    plt.plot(pulses_x, x_pred, color='red', label='Fitted X')
    plt.xlabel('X Direction Pulses')
    plt.ylabel('X Coordinate')
    plt.title('X Coordinate vs X Direction Pulses')
    plt.legend()

    # 绘制 Y 坐标与 Y 方向脉冲数的拟合曲线
    plt.subplot(1, 2, 2)
    plt.scatter(pulses_y, y, color='green', label='Actual Y')
    plt.plot(pulses_y, y_pred, color='red', label='Fitted Y')
    plt.xlabel('Y Direction Pulses')
    plt.ylabel('Y Coordinate')
    plt.title('Y Coordinate vs Y Direction Pulses')
    plt.legend()

    plt.tight_layout()
    plt.show()

    # 打印模型参数
    print(f'X Coordinate vs X Direction Pulses: Coefficients: {model_x.coef_}, Intercept: {model_x.intercept_}')
    print(f'Y Coordinate vs Y Direction Pulses: Coefficients: {model_y.coef_}, Intercept: {model_y.intercept_}')


# 输入数据
x = np.array([109, 167, 134, 164, 109, 112, 50, 50, 49])
y = np.array([120, 119,181, 59, 59, 184, 122, 185, 61])
pulses_x = np.array([0, 0, 1500, -1500, -1500, 1500, 0, 1500, -1500])
pulses_y = np.array([3300, 1800, 1800, 1800, 3300, 3300, 4800, 4800, 4800])

# 进行线性回归并绘图
linear_regression_and_plot(x, y, pulses_x, pulses_y)
