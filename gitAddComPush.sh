#!/usr/bin/env bash

read -p "Branch: " branch
read -p "Message: " message

git add -A
git commit -m "$message"
git push origin $branch
