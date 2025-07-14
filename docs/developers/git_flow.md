# Git 工作流说明文档

本项目采用简化版 Git Flow 分支模型 + 语义化版本控制（SemVer），以保障协作开发、版本可控与持续交付。

---

## 一、分支策略

| 分支名称       | 用途说明                   |
|----------------|----------------------------|
| `main`         | 线上稳定版本               |
| `dev`          | 日常开发主干               |
| `feature/*`    | 开发新功能（从 dev 分出）  |
| `hotfix/*`     | 修复线上 bug（从 main 分出）|
| `release/*`    | 发布准备（从 dev 分出）    |

---

## 二、提交信息规范（Conventional Commits）

统一格式：
```txt
<type>(<scope>): <subject>
```

示例：  

feat(api): 添加练习模块导入功能  
fix(login): 修复 token 过期逻辑  
docs(readme): 补充本地启动说明  

常用类型说明：

| 类型      | 说明                     |
|-----------|--------------------------|
| feat      | 新功能                   |
| fix       | 修复问题                 |
| docs      | 文档更新                 |
| style     | 代码格式，不影响功能     |
| refactor  | 重构代码，功能不变       |
| test      | 添加或修改测试           |
| chore     | 其他修改（构建、脚本等）|

建议使用工具提交规范信息：

```bash
npm install -g commitizen
git cz
```

## 三、开发流程建议  

### 1. 开发新功能
```bash
git checkout dev
git pull
git checkout -b feature/xxx-module
# 编码、调试...
git add .
git commit -m "feat(module): 实现 xxx 功能"
git push origin feature/xxx-module
```
合并至 dev：
```bash
git checkout dev
git merge feature/xxx-module
git push origin dev
```
### 2. 发布流程  

```bash
git checkout dev
git pull
git checkout -b release/1.2.0
# 做最后测试、优化...
git checkout main
git merge release/1.2.0
bash bump_version.sh PATCH    # 或 MINOR / MAJOR
git push origin main --tags
```
## 四、语义化版本控制（Semantic Versioning）  

版本号格式：
```txt
MAJOR.MINOR.PATCH
```
说明：

| 类型 | 说明 |
| :---: | :---: |
| MAJOR	| 破坏性变更，不兼容原版本 |
| MINOR | 添加新功能，兼容原版本 |
| PATCH | 修复 bug，兼容原版本 |

当前版本号记录在根目录下 VERSION 文件中。

## 五、版本更新脚本使用说明  

自动化更新版本号、提交并打标签：
```bash
bash bump_version.sh PATCH   # 或 MINOR / MAJOR
```
该脚本功能：

- 自动修改 VERSION
- 自动 git commit 并打 git tag
---