#!/bin/bash

set -e

# 读取当前版本
VERSION=$(cat VERSION)

# 检查未提交改动
if [[ -n $(git status --porcelain) ]]; then
  echo "❌ 有未提交的修改，请先提交再发布！"
  exit 1
fi

# 创建 Git tag
git tag "v$VERSION"

# 生成 CHANGELOG（若安装了 git-chglog）
if command -v git-chglog &>/dev/null; then
  git-chglog -o CHANGELOG.md
  git add CHANGELOG.md
  git commit -m "docs(changelog): update CHANGELOG for v$VERSION"
fi

# 推送代码和 tag
git push origin main --tags

echo "✅ 发布完成：v$VERSION"
