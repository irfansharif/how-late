
#
# This file is the default set of rules to compile a Pebble project.
#
# Feel free to customize this to your needs.
#

# Use the python sh module to run the jshint command
from sh import jshint
import os.path

top = '.'
out = 'build'

def options(ctx):
    ctx.load('pebble_sdk')

def configure(ctx):
    ctx.load('pebble_sdk')
    jshint.bake(['--config', './pebble-jshintrc'])

def js_jshint(task):
    inputs = (input.abspath() for input in task.inputs)
    jshint(*inputs)

def build(ctx):
    ctx.load('pebble_sdk')

    # Run jshint before compiling the app.
    # jshint("src/js/pebble-js-app.js")

    js_sources = [
      'src/js/pebble-js-app.js'
    ]
    ctx(rule=js_jshint, source=js_sources)


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
