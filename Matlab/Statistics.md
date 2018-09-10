# 统计 Statistics

## 描述性统计 Descriptive Statistics

### 集中趋势 Central Tendency

#### 平均数 Mean

`mean()`：计算array的平均数

#### 中位数 Median

`median()`：计算array的中位数

#### 众数 Mode

`mode()`：计算array的众数

### 四分点 Quartile

`prctile()`在一般大量样本之情况下，利用百分值去确定样本之合理对应值 

```matlab
dataset = [1 2 44 11 44 55 22 11 10 33];
p = 20; % 百分比，范围为0~100
Y = prctile(dataset, p)
```

### 离散程度 Variation

#### 范围 Range

`max()` ：计算array的最大值

`min()` ：计算array的最小值

#### 方差 Variance

`var()` : 计算array的方差

#### 标准差 Standard Deviation

`std()` ：计算array的标准差

### 数据绘图

#### Boxplot()

```matlab
marks = [80 81 81 84 88 92 92 94 96 97];
boxplot(marks) % 同时画出四分点的位置
prctile(marks,[25 50 75]) % 不会影响boxplot画图
```

#### 离散图 scatter()

```matlab
x = [-1, 2 -0.5 0.3 0.9 1.8 2.6 3 3.5];
y = [-15 6 -8.5 2.2 4.5 6.6 8.2 8.9 10.0];
scatter(x,y);
```



## 推论性统计 Inferential Statistics

### 假设检验 Hypothesis Testing

Function | illustration
--- | ---
ranksum() | Wilcoxon rank sum test
signrank() | Wilcoxon signed rank test
ttest() | One-sample and paired-sample t-test
ttest2() | Two-sample t-test
ztest() | z-test

例：$ 已知\sigma_1 =\sigma_2 \quad H_0: \, \mu_1 = \mu_2 \quad H_1: \,\mu_1 \neq \mu_2$

```matlab
x1 = [1 2 3 4 5 4 3 2 1];
x2 = [1 2 3 4 5 6 7 8 9];
alpha = 0.05;
[h, p] = ttest2(x1,x2,alpha); % h=1/h=0代表是否拒绝原假设, p<alpha时拒绝原假设，否则接受原假设
```



