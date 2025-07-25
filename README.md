# 参商 ShenShang

> “参不在宿，商不在辰” ——《诗经·小雅》  
> 星辰虽遥，不止不息。参商，寓意在遥不可及中砥砺追求。

---

## 📘 项目简介

**参商** 是一个面向移动端与 Web 的现代化**练习与考试系统**，旨在为用户提供高性能、高可用、模块化的在线训练与考核平台。系统名称源自古星宿“参星与商星”，寓意**不懈探索、上下求索的学习之道**。

本项目采用 **C++** 与 **Vue 3** 构建，后端聚焦性能与并发优化，前端注重交互体验与组件灵活性。系统架构支持多模块扩展、日志追踪与自动化处理，适用于高校教学平台、技能训练系统、线上测评工具等多种场景。

---

## 📁 项目结构

```bash
ShenShang/
├── backend/            # C++ 编写的高性能后端服务
│   ├── include/        # 头文件目录（封装、继承、模块接口）
│   ├── src/            # 核心业务逻辑实现
│   ├── scripts/        # 自动化构建与测试脚本
│   └── tests/          # 单元测试模块
├── frontend/           # Vue 3 前端页面
│   ├── src/            # 页面、组件、路由、API 接口
│   ├── public/         # 静态资源
│   └── tailwind.config.js  # 前端样式定制
├── docs/               # 自动化文档与使用手册
├── config/             # 配置文件（数据库、日志、运行参数）
└── README.md           # 项目说明文档
