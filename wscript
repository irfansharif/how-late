
#
# This file is the default set of rules to compile a Pebble project.
#
# Feel free to customize this to your needs.
#

from sh import uglifyjs
from sh import jshint
import os.path
import json

top = '.'
out = 'build'

def options(ctx):
    ctx.load('pebble_sdk')

def configure(ctx):
    ctx.load('pebble_sdk')
    jshint.bake(['--config', './pebble-jshintrc'])

def concatenate_js(task):
  inputs = (input.abspath() for input in task.inputs)
  uglifyjs(*inputs, o=task.outputs[0].abspath())

def js_jshint(task):
    inputs = (input.abspath() for input in task.inputs)
    jshint(*inputs)

def generate_appinfo_h(task):
  ext_out = '.c'
  src = task.inputs[0].abspath()
  target = task.outputs[0].abspath()
  appinfo = json.load(open(src))

  f = open(target, 'w')
  f.write('#pragma once\n\n')
  f.write('#define VERSION_LABEL "{0}"\n'.format(appinfo["versionLabel"]))
  f.write('#define UUID "{0}"\n'.format(appinfo["uuid"]))
  for key in appinfo['appKeys']:
    f.write('#define APP_KEY_{0} {1}\n'.format(key.upper(), appinfo['appKeys'][key]))
  f.close()

def build(ctx):
    ctx.load('pebble_sdk')

    js_sources = [
      'src/js/app.js',
      'src/js/config.js',
      'src/js/request.js',
      'src/js/class-functions.js',
      'src/js/mock-data.js',
      'src/js/token-management.js'
    ]
    built_js = 'src/js/pebble-js-app.js'

    ctx(rule=js_jshint, source=js_sources)
    ctx(rule=concatenate_js, source=' '.join(js_sources), target=built_js)
    ctx(rule=generate_appinfo_h, source='appinfo.json', target='src/generated/appinfo.h')

    build_worker = os.path.exists('worker_src')
    binaries = []

    for p in ctx.env.TARGET_PLATFORMS:
        ctx.set_env(ctx.all_envs[p])
        ctx.set_group(ctx.env.PLATFORM_NAME)
        app_elf='{}/pebble-app.elf'.format(ctx.env.BUILD_DIR)
        ctx.pbl_program(source=ctx.path.ant_glob('src/**/*.c'),
        target=app_elf)

        if build_worker:
            worker_elf='{}/pebble-worker.elf'.format(ctx.env.BUILD_DIR)
            binaries.append({'platform': p, 'app_elf': app_elf, 'worker_elf': worker_elf})
            ctx.pbl_worker(source=ctx.path.ant_glob('worker_src/**/*.c'),
            target=worker_elf)
        else:
            binaries.append({'platform': p, 'app_elf': app_elf})

    ctx.set_group('bundle')
    ctx.pbl_bundle(binaries=binaries, js=ctx.path.ant_glob('src/js/**/*.js'))
