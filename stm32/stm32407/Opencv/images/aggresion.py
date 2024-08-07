import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression


# 生成随机数据并训练模型
def train_model():
    x = [109, 167, 134, 164, 109, 112, 50, 50, 49, 120]  # 模拟棋子在棋盘上的X坐标

    y = [119, 181, 59, 59, 184, 122, 185, 61]  # 模拟棋子在棋盘上的Y坐标
    pulses = []

    X = np.vstack((x, y)).T  # 将X和Y坐标合并为一个矩阵

    # 创建线性回归模型并进行训练
    model = LinearRegression()
    model.fit(X, pulses)

    return model


# 使用模型预测步进电机的脉冲数
def predict_pulses(model, coordinates):
    coordinates = np.array(coordinates)
    if coordinates.ndim == 1:
        coordinates = coordinates.reshape(1, -1)
    return model.predict(coordinates)


# 绘制数据和拟合结果
def plot_results(model, x, y, pulses):
    X = np.vstack((x, y)).T  # 将X和Y坐标合并为一个矩阵
    pulses_pred = model.predict(X)

    plt.figure(figsize=(10, 6))
    plt.scatter(x, y, c=pulses, cmap='viridis', label='Data points')
    plt.colorbar(label='Pulses')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')

    # 绘制预测结果
    for i in range(len(x)):
        plt.plot([x[i], x[i]], [y[i], y[i]], 'ro-', alpha=0.3)  # 使用线段表示预测值
    plt.title('Linear Regression Fit')
    plt.legend()
    plt.show()


# 主程序
if __name__ == "__main__":
    model = train_model()

    # 打印模型参数
    print(f'Coefficients: {model.coef_}')
    print(f'Intercept: {model.intercept_}')

    # 测试点
    test_coordinates = [(10, 20), (30, 40), (50, 60)]
    predictions = predict_pulses(model, test_coordinates)
    print(f'Predictions for {test_coordinates}: {predictions}')

    # 绘制结果
    np.random.seed(42)
    x = np.random.uniform(0, 100, 50)
    y = np.random.uniform(0, 100, 50)
    pulses = 3 * x + 5 * y + np.random.normal(0, 10, 50)
    plot_results(model, x, y, pulses)
