#!/usr/bin/env bash

bazel build \
    //cyber/... \
    //modules/bridge/... \
    //modules/canbus/... \
    //modules/common/... \
    //modules/control/... \
    //modules/data/... \
    //modules/dreamview/... \
    //modules/guardian/... \
    //modules/monitor/... \
    //modules/prediction/... \
    //modules/routing/... \
    //modules/storytelling/... \
    //modules/tools/... \
    //modules/transform/...
