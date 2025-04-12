#!/bin/bash
git checkout stg
git merge dev
git tag "stg-$(date +%Y%m%d%H%M)"
git push origin stg --tags
