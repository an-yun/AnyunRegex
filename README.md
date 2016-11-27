<div style="visibility: hidden; overflow: hidden; position: absolute; top: 0px; height: 1px; width: auto; padding: 0px; border: 0px; margin: 0px; text-align: left; text-indent: 0px; text-transform: none; line-height: normal; letter-spacing: normal; word-spacing: normal;"><div id="MathJax_SVG_Hidden"></div><svg><defs id="MathJax_SVG_glyphs"><path id="MJMATHI-3F5" stroke-width="1" d="M227 -11Q149 -11 95 41T40 174Q40 262 87 322Q121 367 173 396T287 430Q289 431 329 431H367Q382 426 382 411Q382 385 341 385H325H312Q191 385 154 277L150 265H327Q340 256 340 246Q340 228 320 219H138V217Q128 187 128 143Q128 77 160 52T231 26Q258 26 284 36T326 57T343 68Q350 68 354 58T358 39Q358 36 357 35Q354 31 337 21T289 0T227 -11Z"></path><path id="MJMATHI-65" stroke-width="1" d="M39 168Q39 225 58 272T107 350T174 402T244 433T307 442H310Q355 442 388 420T421 355Q421 265 310 237Q261 224 176 223Q139 223 138 221Q138 219 132 186T125 128Q125 81 146 54T209 26T302 45T394 111Q403 121 406 121Q410 121 419 112T429 98T420 82T390 55T344 24T281 -1T205 -11Q126 -11 83 42T39 168ZM373 353Q367 405 305 405Q272 405 244 391T199 357T170 316T154 280T149 261Q149 260 169 260Q282 260 327 284T373 353Z"></path><path id="MJMAIN-31" stroke-width="1" d="M213 578L200 573Q186 568 160 563T102 556H83V602H102Q149 604 189 617T245 641T273 663Q275 666 285 666Q294 666 302 660V361L303 61Q310 54 315 52T339 48T401 46H427V0H416Q395 3 257 3Q121 3 100 0H88V46H114Q136 46 152 46T177 47T193 50T201 52T207 57T213 61V578Z"></path><path id="MJMAIN-32" stroke-width="1" d="M109 429Q82 429 66 447T50 491Q50 562 103 614T235 666Q326 666 387 610T449 465Q449 422 429 383T381 315T301 241Q265 210 201 149L142 93L218 92Q375 92 385 97Q392 99 409 186V189H449V186Q448 183 436 95T421 3V0H50V19V31Q50 38 56 46T86 81Q115 113 136 137Q145 147 170 174T204 211T233 244T261 278T284 308T305 340T320 369T333 401T340 431T343 464Q343 527 309 573T212 619Q179 619 154 602T119 569T109 550Q109 549 114 549Q132 549 151 535T170 489Q170 464 154 447T109 429Z"></path><path id="MJMATHI-61" stroke-width="1" d="M33 157Q33 258 109 349T280 441Q331 441 370 392Q386 422 416 422Q429 422 439 414T449 394Q449 381 412 234T374 68Q374 43 381 35T402 26Q411 27 422 35Q443 55 463 131Q469 151 473 152Q475 153 483 153H487Q506 153 506 144Q506 138 501 117T481 63T449 13Q436 0 417 -8Q409 -10 393 -10Q359 -10 336 5T306 36L300 51Q299 52 296 50Q294 48 292 46Q233 -10 172 -10Q117 -10 75 30T33 157ZM351 328Q351 334 346 350T323 385T277 405Q242 405 210 374T160 293Q131 214 119 129Q119 126 119 118T118 106Q118 61 136 44T179 26Q217 26 254 59T298 110Q300 114 325 217T351 328Z"></path></defs></svg></div><div id="wmd-preview" class="wmd-preview"><div class="md-section-divider"></div><div class="md-section-divider"></div><h1 data-anchor-id="nnm8" id="使用c编写的正则表达式引擎">使用C++编写的正则表达式引擎</h1><hr><div class="md-section-divider"></div><h2 data-anchor-id="5kn5" id="目录">目录</h2><p data-anchor-id="szrv"><div class="toc">
<ul>
<li><a href="#使用c编写的正则表达式引擎">使用C++编写的正则表达式引擎</a><ul>
<li><a href="#目录">目录</a></li>
<li><a href="#关于本项目">关于本项目</a></li>
<li><a href="#实现思路">实现思路</a><ul>
<li><a href="#1-正则表达式运行符和优先级">1. 正则表达式运行符和优先级</a><ul>
<li><a href="#优先级表">优先级表：</a></li>
</ul>
</li>
<li><a href="#2-正则表达式和nfa一一对应关系">2. 正则表达式和NFA一一对应关系</a><ul>
<li><a href="#说明">说明：</a></li>
</ul>
</li>
<li><a href="#3-匹配过程">3. 匹配过程</a></li>
</ul>
</li>
<li><a href="#使用示例及说明">使用示例及说明</a><ul>
<li><a href="#1-功能和代码示例">1. 功能和代码示例</a></li>
<li><a href="#2-包含文件说明">2. 包含文件说明</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</p><hr><div class="md-section-divider"></div><h2 data-anchor-id="6hlo" id="关于本项目">关于本项目</h2><p data-anchor-id="rme4">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个项目开始写于2016年10月14日，当时在本科的毕业设计应该些什么，后来在知乎上看到vczh的篇介绍正则表达式的文章，就有了一些想法。整个项目没有任何现有的正则表达式库的代码，全部自己写成，同时有大量的测试，测试的基准是C++11 regex。 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在后来的项目中，使用正则表达式结合爬虫分析招标公告，招标文件在和小组成员完成了一个招投标系统，系统可以自动分析抓取政府网站公开的招标公告，然后通过爬虫抓取下来，利用正则表达式进行分析，将分析结果存入数据库，然后通过web网站展示出来</p><hr><div class="md-section-divider"></div><h2 data-anchor-id="efzq" id="实现思路">实现思路</h2><p data-anchor-id="ez05">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;因为正则表达式和非确定有限状态自动机NFA是完全等价的<a href="#fn:footnote" id="fnref:footnote" title="查看注脚" class="footnote">[1]</a>，所以可以把一个正则表达式一一对应的翻译成一个NFA（下面会详细说明） <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;整体上，先把输入的正则表达式通过算符优先文法判断优先级，然后根据不同的优先级的运算符按照优先级，把每一部分的正则表达翻译成对应的有限状态自动机（分确定有限状态自动机DFA和非确定有限状态自动机NFA）。翻译后的有限状态自动机对应一个有向图，有一个起点（代表起始状态），有一个终点（代表终止状态，多个终点可以把它们用空边<span class="MathJax_Preview"></span><span class="MathJax_SVG" id="MathJax-Element-1-Frame" role="textbox" aria-readonly="true" style="font-size: 100%; display: inline-block;"><svg xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 -452.0516853480245 406.5 484.10337069604896" style="width: 0.927ex; height: 1.158ex; vertical-align: -0.116ex; margin: 1px 0px;"><g stroke="black" fill="black" stroke-width="0" transform="matrix(1 0 0 -1 0 0)"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMATHI-3F5"></use></g></svg></span><script type="math/tex" id="MathJax-Element-1">\epsilon</script>连接到唯一的终点上） <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;进行匹配的时候，记录匹配的信息，通过实时的匹配信息，结合有限状态自动机就可以从一个状态跳转到下一个状态，如果能到达说明匹配成功率</p><div class="md-section-divider"></div><h3 data-anchor-id="smst" id="1-正则表达式运行符和优先级">1. 正则表达式运行符和优先级</h3><div class="md-section-divider"></div><h4 data-anchor-id="y5qd" id="优先级表">优先级表：</h4><ul data-anchor-id="up9d">
<li><code>-1</code>代表左边的优先级小于右边</li>
<li><code>0</code> &nbsp;代表左边的优先级等于右边(对应的操作是出栈)</li>
<li><code>+1</code> 代表左边的优先级大于右边</li>
<li><code>error</code> 代表出错，一般的情况是缺少括号</li>
<li>有些非运算符没有画出,如：<code>,</code>,<code>'</code>,<code>.</code>等等</li>
</ul><table data-anchor-id="abxb" class="table table-striped-white table-bordered">
<thead>
<tr>
 <th style="text-align:center;">符号</th>
 <th style="text-align:center;">'\0'</th>
 <th style="text-align:center;">' \'</th>
 <th style="text-align:center;">' ('</th>
 <th style="text-align:center;">' )'</th>
 <th style="text-align:center;">' ?'</th>
 <th style="text-align:center;">' *'</th>
 <th style="text-align:center;">' ^'</th>
 <th style="text-align:center;">'<span>$</span>'</th>
 <th style="text-align:center;">' +'</th>
 <th style="text-align:center;">' {'</th>
 <th style="text-align:center;">' }'</th>
 <th style="text-align:center;">' ['</th>
 <th style="text-align:center;">' ]'</th>
 <th style="text-align:center;">'|'</th>
</tr>
</thead>
<tbody><tr>
 <td style="text-align:center;"><strong>'\0'</strong></td>
 <td style="text-align:center;">0</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' \'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' ('</strong></td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">0</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' )'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' ?'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' *'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' ^'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' $'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' +'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' {'</strong></td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">0</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' }'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' ['</strong></td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>' ]'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">0</td>
 <td style="text-align:center;">+1</td>
</tr>
<tr>
 <td style="text-align:center;"><strong>'|'</strong></td>
 <td style="text-align:center;">+1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">error</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">-1</td>
 <td style="text-align:center;">+1</td>
</tr>
</tbody></table><p data-anchor-id="4t3r">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>\0</code>代表起始或者结束符 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>\</code>&nbsp;代表转义符号（和大多数编程语言中一样） <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>^</code>&nbsp;在<code>[]</code>外代表取补集，其它地方代表行起始位置</p><div class="md-section-divider"></div><h3 data-anchor-id="2xl5" id="2-正则表达式和nfa一一对应关系">2. 正则表达式和NFA一一对应关系</h3><div class="md-section-divider"></div><h4 data-anchor-id="eyvu" id="说明">说明：</h4><ul data-anchor-id="wg1p">
<li>小写字母代表单个的终结符如a,b,c，表示输入的一个字符<code>'a'</code>,<code>'1'</code>等等</li>
<li>正则表达式统一用<code>e</code>加下标表示,如<span class="MathJax_Preview"></span><span class="MathJax_SVG" id="MathJax-Element-2-Frame" role="textbox" aria-readonly="true" style="font-size: 100%; display: inline-block;"><svg xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 -464.0516853480245 920.406943983867 634.8104774772355" style="width: 2.085ex; height: 1.506ex; vertical-align: -0.463ex; margin: 1px 0px;"><g stroke="black" fill="black" stroke-width="0" transform="matrix(1 0 0 -1 0 0)"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMATHI-65"></use><use transform="scale(0.7071067811865476)" xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMAIN-31" x="659" y="-213"></use></g></svg></span><script type="math/tex" id="MathJax-Element-2">e_1</script>,<span class="MathJax_Preview"></span><span class="MathJax_SVG" id="MathJax-Element-3-Frame" role="textbox" aria-readonly="true" style="font-size: 100%; display: inline-block;"><svg xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 -464.0516853480245 920.406943983867 634.8104774772355" style="width: 2.085ex; height: 1.506ex; vertical-align: -0.463ex; margin: 1px 0px;"><g stroke="black" fill="black" stroke-width="0" transform="matrix(1 0 0 -1 0 0)"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMATHI-65"></use><use transform="scale(0.7071067811865476)" xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMAIN-32" x="659" y="-213"></use></g></svg></span><script type="math/tex" id="MathJax-Element-3">e_2</script>,<span class="MathJax_Preview"></span><span class="MathJax_SVG" id="MathJax-Element-4-Frame" role="textbox" aria-readonly="true" style="font-size: 100%; display: inline-block;"><svg xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 -462.0516853480245 529.5 493.10337069604896" style="width: 1.274ex; height: 1.158ex; vertical-align: -0.116ex; margin: 1px 0px;"><g stroke="black" fill="black" stroke-width="0" transform="matrix(1 0 0 -1 0 0)"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#MJMATHI-61"></use></g></svg></span><script type="math/tex" id="MathJax-Element-4">a</script>等等</li>
</ul><p data-anchor-id="y3p7"><img src="https://github.com/an-yun/AnyunRegex/raw/master/img/a.png" alt="单个a" title=""> <br>
<br>
<br>
<img src="https://github.com/an-yun/AnyunRegex/raw/master/img/e1_or_e2.png" alt="单个a" title=""></p><div class="md-section-divider"></div><h3 data-anchor-id="z1yx" id="3-匹配过程">3. 匹配过程</h3><hr><div class="md-section-divider"></div><h2 data-anchor-id="ggm3" id="使用示例及说明">使用示例及说明</h2><div class="md-section-divider"></div><h3 data-anchor-id="2v98" id="1-功能和代码示例">1. 功能和代码示例</h3><div class="md-section-divider"></div><pre class="prettyprint linenums prettyprinted" data-anchor-id="075a"><ol class="linenums"><li class="L0"><code class="language-C++"><span class="com">#include</span><span class="pln"> </span><span class="str">&lt;iostream&gt;</span></code></li><li class="L1"><code class="language-C++"><span class="com">#include</span><span class="pln"> </span><span class="str">&lt;string&gt;</span></code></li><li class="L2"><code class="language-C++"><span class="com">#include</span><span class="pln"> </span><span class="str">&lt;fstream&gt;</span></code></li><li class="L3"><code class="language-C++"><span class="com">#include</span><span class="pln"> </span><span class="str">"Regex/Matcher.h"</span></code></li><li class="L4"><code class="language-C++"></code></li><li class="L5"><code class="language-C++"><span class="kwd">using</span><span class="pln"> </span><span class="kwd">namespace</span><span class="pln"> anyun_regex</span><span class="pun">;</span></code></li><li class="L6"><code class="language-C++"><span class="kwd">using</span><span class="pln"> </span><span class="kwd">namespace</span><span class="pln"> std</span><span class="pun">;</span></code></li><li class="L7"><code class="language-C++"></code></li><li class="L8"><code class="language-C++"><span class="com">#define</span><span class="pln"> </span><span class="typ">Println</span><span class="pun">(</span><span class="pln">content</span><span class="pun">)</span><span class="pln"> \</span></code></li><li class="L9"><code class="language-C++"><span class="pln">    cout</span><span class="pun">&lt;&lt;</span><span class="pln">content</span><span class="pun">&lt;&lt;</span><span class="pln">endl</span><span class="pun">;</span></code></li><li class="L0"><code class="language-C++"></code></li><li class="L1"><code class="language-C++"><span class="kwd">void</span><span class="pln"> password_validate</span><span class="pun">()</span></code></li><li class="L2"><code class="language-C++"><span class="pun">{</span></code></li><li class="L3"><code class="language-C++"><span class="pln">    </span><span class="kwd">string</span><span class="pln"> passwords</span><span class="pun">[]</span><span class="pln"> </span><span class="pun">=</span></code></li><li class="L4"><code class="language-C++"><span class="pln">    </span><span class="pun">{</span><span class="pln"> </span><span class="str">"aaaa1111"</span><span class="pun">,</span></code></li><li class="L5"><code class="language-C++"><span class="pln">        </span><span class="str">"aa123"</span><span class="pun">,</span></code></li><li class="L6"><code class="language-C++"><span class="pln">        </span><span class="str">"123"</span><span class="pun">,</span></code></li><li class="L7"><code class="language-C++"><span class="pln">        </span><span class="str">"1123445690aaa"</span><span class="pun">,</span></code></li><li class="L8"><code class="language-C++"><span class="pln">        </span><span class="str">"abcd"</span><span class="pun">,</span></code></li><li class="L9"><code class="language-C++"><span class="pln">        </span><span class="str">"aabbccc"</span><span class="pun">,</span></code></li><li class="L0"><code class="language-C++"><span class="pln">        </span><span class="str">"11123"</span><span class="pln"> </span><span class="pun">};</span></code></li><li class="L1"><code class="language-C++"><span class="pln">    NFA pattern</span><span class="pun">(</span><span class="str">"(\\w)\\1{2,}"</span><span class="pun">);</span></code></li><li class="L2"><code class="language-C++"><span class="pln">    </span><span class="kwd">for</span><span class="pln"> </span><span class="pun">(</span><span class="kwd">string</span><span class="pln"> </span><span class="pun">&amp;</span><span class="pln">password </span><span class="pun">:</span><span class="pln"> passwords</span><span class="pun">)</span></code></li><li class="L3"><code class="language-C++"><span class="pln">    </span><span class="pun">{</span></code></li><li class="L4"><code class="language-C++"><span class="pln">        </span><span class="typ">NFAMatcher</span><span class="pln"> matcher </span><span class="pun">=</span><span class="pln"> </span><span class="typ">NFAMatcher</span><span class="pun">::</span><span class="pln">match</span><span class="pun">(</span><span class="pln">password</span><span class="pun">,</span><span class="pln"> pattern</span><span class="pun">);</span></code></li><li class="L5"><code class="language-C++"><span class="pln">        </span><span class="typ">Println</span><span class="pun">(</span><span class="str">"验证密码："</span><span class="pln"> </span><span class="pun">+</span><span class="pln"> password</span><span class="pun">);</span></code></li><li class="L6"><code class="language-C++"><span class="pln">        </span><span class="kwd">if</span><span class="pln"> </span><span class="pun">(</span><span class="pln">matcher</span><span class="pun">.</span><span class="pln">find</span><span class="pun">())</span></code></li><li class="L7"><code class="language-C++"><span class="pln">        </span><span class="pun">{</span></code></li><li class="L8"><code class="language-C++"><span class="pln">            </span><span class="typ">Println</span><span class="pun">(</span><span class="str">"包含重复3个以上,重复段为"</span><span class="pun">);</span></code></li><li class="L9"><code class="language-C++"><span class="pln">            </span><span class="typ">Println</span><span class="pun">(</span><span class="pln">matcher</span><span class="pun">.</span><span class="kwd">group</span><span class="pun">());</span></code></li><li class="L0"><code class="language-C++"><span class="pln">        </span><span class="pun">}</span></code></li><li class="L1"><code class="language-C++"><span class="pln">        </span><span class="kwd">else</span></code></li><li class="L2"><code class="language-C++"><span class="pln">            </span><span class="typ">Println</span><span class="pun">(</span><span class="str">"OK"</span><span class="pun">);</span></code></li><li class="L3"><code class="language-C++"><span class="pln">        </span><span class="typ">Println</span><span class="pun">(</span><span class="str">""</span><span class="pun">);</span></code></li><li class="L4"><code class="language-C++"><span class="pln">    </span><span class="pun">}</span></code></li><li class="L5"><code class="language-C++"><span class="pln">    cout </span><span class="pun">&lt;&lt;</span><span class="pln"> endl</span><span class="pun">;</span></code></li><li class="L6"><code class="language-C++"><span class="pun">}</span></code></li><li class="L7"><code class="language-C++"><span class="kwd">int</span><span class="pln"> main</span><span class="pun">()</span></code></li><li class="L8"><code class="language-C++"><span class="pun">{</span></code></li><li class="L9"><code class="language-C++"><span class="pln">    password_validate</span><span class="pun">();</span></code></li><li class="L0"><code class="language-C++"><span class="pln">    </span><span class="kwd">return</span><span class="pln"> </span><span class="lit">0</span><span class="pun">;</span></code></li><li class="L1"><code class="language-C++"><span class="pun">}</span></code></li></ol></pre><p data-anchor-id="82dl">运行结果：</p><div class="md-section-divider"></div><pre class="prettyprint linenums prettyprinted" data-anchor-id="alef"><ol class="linenums"><li class="L0"><code><span class="pun">验证密码：</span><span class="pln">aaaa1111</span></code></li><li class="L1"><code><span class="pun">包含重复</span><span class="lit">3</span><span class="pun">个以上,重复段为</span></code></li><li class="L2"><code><span class="pln">aaaa</span></code></li><li class="L3"><code></code></li><li class="L4"><code><span class="pun">验证密码：</span><span class="pln">aa123</span></code></li><li class="L5"><code><span class="pln">OK</span></code></li><li class="L6"><code></code></li><li class="L7"><code><span class="pun">验证密码：</span><span class="lit">123</span></code></li><li class="L8"><code><span class="pln">OK</span></code></li><li class="L9"><code></code></li><li class="L0"><code><span class="pun">验证密码：</span><span class="lit">1123445690aaa</span></code></li><li class="L1"><code><span class="pun">包含重复</span><span class="lit">3</span><span class="pun">个以上,重复段为</span></code></li><li class="L2"><code><span class="pln">aaa</span></code></li><li class="L3"><code></code></li><li class="L4"><code><span class="pun">验证密码：</span><span class="pln">abcd</span></code></li><li class="L5"><code><span class="pln">OK</span></code></li><li class="L6"><code></code></li><li class="L7"><code><span class="pun">验证密码：</span><span class="pln">aabbccc</span></code></li><li class="L8"><code><span class="pun">包含重复</span><span class="lit">3</span><span class="pun">个以上,重复段为</span></code></li><li class="L9"><code><span class="pln">ccc</span></code></li><li class="L0"><code></code></li><li class="L1"><code><span class="pun">验证密码：</span><span class="lit">11123</span></code></li><li class="L2"><code><span class="pun">包含重复</span><span class="lit">3</span><span class="pun">个以上,重复段为</span></code></li><li class="L3"><code><span class="lit">111</span></code></li></ol></pre><hr><div class="md-section-divider"></div><h3 data-anchor-id="n3ho" id="2-包含文件说明">2. 包含文件说明</h3><p data-anchor-id="jmd6">Regex/Matcher.h <br>
Regex/NFA.h <br>
Regex/DirectedGraph.h</p><hr><div class="footnotes" data-anchor-id="g39a">
<hr>
<small>

<span id="fn:footnote">[1] </span>这是一个 <em>注脚</em> 的 <strong>文本</strong>。 <a href="#fnref:footnote" title="回到文稿" class="reversefootnote">↩</a><br>

</small>
</div></div>