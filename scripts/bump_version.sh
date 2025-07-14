#!/bin/bash
# 用法: bash bump_version.sh [PATCH|MINOR|MAJOR]

VERSION_FILE="VERSION"

if [[ ! -f "$VERSION_FILE" ]]; then
  echo "0.0.0" > "$VERSION_FILE"
fi

OLD_VERSION=$(cat "$VERSION_FILE")
IFS='.' read -r MAJOR MINOR PATCH <<< "$OLD_VERSION"

case "$1" in
  MAJOR)
    ((MAJOR+=1))
    MINOR=0
    PATCH=0
    ;;
  MINOR)
    ((MINOR+=1))
    PATCH=0
    ;;
  PATCH)
    ((PATCH+=1))
    ;;
  *)
    echo "❌ 用法: bash bump_version.sh [PATCH|MINOR|MAJOR]"
    exit 1
    ;;
esac

NEW_VERSION="$MAJOR.$MINOR.$PATCH"
echo "$NEW_VERSION" > "$VERSION_FILE"

git add VERSION
git commit -m "chore: bump version to $NEW_VERSION"
git tag "v$NEW_VERSION"

echo "✅ 版本已更新: $OLD_VERSION → $NEW_VERSION"