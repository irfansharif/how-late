# How-Late
Pebble Time (Basalt) app integrating with Google Calendar API 


#### Contributing

> Fork this current repository

```sh
git clone https://github.com/[YOUR-GITHUB-USERNAME]/how-late.git
git remote add upstream https://github.com/irfansharif/how-late.git
git checkout -b my-new-feature
git commit -am 'Add some feature'
git push origin my-new-feature
```
> Create a new pull request


#### Compiling
> Download and install the latest SDK from http://developer.getpebble.com/sdk/

```sh
git clone https://github.com/irfansharif/how-late.git
cd how-late
pebble build && pebble install --emulator basalt
```

#### Debugging
> For debugging purposes add the following to any C & JavaScript code respectively

```C
APP_LOG(APP_LOG_LEVEL_INFO, "Hello, is it me you're looking for?");
```
```JavaScript
console.log('I can see it in your eyes')
```
> To view the logs during runtime in a separate terminal window execute

```sh
pebble logs --emulator basalt
```

#### License
The MIT License (MIT)

Copyright (c) 2015 Irfan Sharif

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


