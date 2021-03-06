/* -*- mode: C; c-basic-offset: 4; intent-tabs-mode: nil -*-
 *
 * STIR -- Sifteo Tiled Image Reducer
 * Micah Elizabeth Scott <micah@misc.name>
 *
 * Copyright <c> 2011 Sifteo, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * AUTOMATICALLY GENERATED by proof_html.py
 * Do not edit by hand!
 */

#include "proof.h"

const char *Stir::ProofWriter::header =
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head> \n"
    "  <script> \n"
    " \n"
    "     /*\n"
    "      * Define a tile pool (per-group)\n"
    "      */\n"
    "\n"
    "     function defineTiles(prefix, tiles) {\n"
    "       for (var i = 0; i < tiles.length; i++) {\n"
    "\n"
    "         // Load it using a Data URI and anonymous img element\n"
    "         var img = new Image();\n"
    "         img.src = prefix + tiles[i];\n"
    "\n"
    "         // Keep a list of closures that can be used to redraw\n"
    "         // every occurrance of this tile in the TileGrids.\n"
    "         img.tgRedraw = []\n"
    " \n"
    "         tiles[i] = img;\n"
    "       }\n"
    "       return tiles;\n"
    "     }\n"
    "\n"
    "     /*\n"
    "      * Object for a single TileGrid, with some interactive features.\n"
    "      * Renders onto an HTML5 Canvas\n"
    "      */\n"
    "\n"
    "     allTileGrids = {};\n"
    "     highlightTile = null;\n"
    "     nextHighlightTile = null;\n"
    "\n"
    "     function TileGrid(pool, canvasId, tileSize) {\n"
    "       var obj = this;\n"
    "\n"
    "       allTileGrids[canvasId] = this;\n"
    "\n"
    "       this.pool = pool;\n"
    "       this.canvas = document.getElementById(\"i\" + canvasId);\n"
    "       this.ctx = this.canvas.getContext(\"2d\");\n"
    "\n"
    "       this.size = tileSize;\n"
    "       this.width = this.canvas.width / this.size;\n"
    "       this.height = this.canvas.height / this.size;\n"
    "       this.mouse = null\n"
    "\n"
    "       this.canvas.onmousemove = function(evt) {\n"
    "         obj.updateMouse([Math.floor(mouseX(evt) / obj.size),\n"
    "                          Math.floor(mouseY(evt) / obj.size)]);\n"
    "       }\n"
    "\n"
    "       this.canvas.onmouseout = function(evt) {\n"
    "         obj.updateMouse(null);\n"
    "       }\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.updateMouse = function(mouse) {\n"
    "       if (mouse)\n"
    "         setTileHighlight(this.tileAt(mouse[0], mouse[1]));\n"
    "       else\n"
    "         setTileHighlight(null);\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.range = function(begin, end) {\n"
    "       var a = [];\n"
    "       for (var i = begin; i < end; i++)\n"
    "         a[i - begin] = i;\n"
    "       this.array(a);\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.array = function(a) {\n"
    "       this.tiles = a;\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.drawAsync = function() {\n"
    "       /*\n"
    "        * Draw the whole TileGrid unconditionally but asynchronously.\n"
    "        * We batch the tiles, drawing one row at a time.\n"
    "        */\n"
    "\n"
    "       for (var y = 0; y < this.height; y++) {\n"
    "         window.setTimeout(function(y, obj){\n"
    "           return function() {\n"
    "             for (var x = 0; x < obj.width; x++)\n"
    "               obj.drawTile(x, y);\n"
    "           }\n"
    "         }(y, this), 0);\n"
    "       }\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.installDrawHandlers = function() {\n"
    "       /*\n"
    "        * Install tile redraw handlers for every tile in the TileGrid\n"
    "        */\n"
    "\n"
    "       for (var y = 0; y < this.height; y++)\n"
    "         for (var x = 0; x < this.width; x++)\n"
    "           var f = function (obj, x, y) {\n"
    "             var t = obj.tileAt(x, y);\n"
    "\n"
    "             if (t) {\n"
    "               t.tgRedraw.push(function() { obj.drawTile(x, y); })\n"
    "             }\n"
    "\n"
    "           } (this, x, y);\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.tileAt = function(x, y) {\n"
    "       /*\n"
    "        * Returns the tile at location (x,y), if any.\n"
    "        */\n"
    "\n"
    "       var i = x + y * this.width;\n"
    "       if (i < this.tiles.length)\n"
    "         return this.pool[this.tiles[i]];\n"
    "     }\n"
    "\n"
    "     TileGrid.prototype.drawTile = function(x, y) {\n"
    "       /*\n"
    "        * (Re)draw a single tile at a specified location on this grid.\n"
    "        */\n"
    "\n"
    "       var tile = this.tileAt(x, y);\n"
    "       if (tile) {\n"
    "\n"
    "         this.ctx.globalAlpha = 1.0;\n"
    "         this.ctx.drawImage(tile, 0, 0, tile.width, tile.height, \n"
    "                            x*this.size, y*this.size, this.size, this.size);\n"
    "\n"
    "         if (tile == highlightTile) {\n"
    "           // Hilight (brighten) this tile\n"
    "           this.ctx.globalAlpha = 0.5;\n"
    "           this.ctx.fillStyle = \"#fff\";\n"
    "           this.ctx.fillRect(x*this.size, y*this.size, this.size, this.size);\n"
    "         }\n"
    "\n"
    "       } else {\n"
    " \n"
    "         // Background\n"
    "         this.ctx.globalAlpha = 1.0;\n"
    "         this.ctx.fillStyle = \"#222\";\n"
    "         this.ctx.fillRect(x*this.size, y*this.size, this.size, this.size);\n"
    "       }\n"
    "     }\n"
    "\n"
    "     function onload() {\n"
    "       /*\n"
    "        * Draw all TileGrids after our images have loaded.\n"
    "        * The drawing itself happens asynchronously, so as not to block the page load.\n"
    "        */\n"
    "\n"
    "       for (var i in allTileGrids) {\n"
    "         allTileGrids[i].installDrawHandlers();\n"
    "         allTileGrids[i].drawAsync();\n"
    "       }\n"
    "     }\n"
    "\n"
    "     function drawTile(t) {\n"
    "       /*\n"
    "        * Redraw a single tile, on every grid.\n"
    "        */\n"
    "\n"
    "       if (t) {\n"
    "         for (var i in t.tgRedraw)\n"
    "           t.tgRedraw[i]();\n"
    "       }\n"
    "     }\n"
    "\n"
    "     function setTileHighlight(t) {\n"
    "       /*\n"
    "        * Change the tile that's currently highlighted.\n"
    "        *\n"
    "        * We do this lazily via a timer callback, to optimize\n"
    "        * out changes that are occurring faster than we can draw them,\n"
    "        * or spurious mouse-out events that occur before moving into a\n"
    "        * different grid.\n"
    "        */\n"
    "\n"
    "       if (nextHighlightTile != t) {\n"
    "         nextHighlightTile = t;\n"
    "\n"
    "         setTimeout(function() {\n"
    "\n"
    "           if (nextHighlightTile != highlightTile) {\n"
    "             var prev = highlightTile;\n"
    "             highlightTile = nextHighlightTile;\n"
    "\n"
    "             /*\n"
    "              * Only draw the affected tiles\n"
    "              */\n"
    "\n"
    "             drawTile(prev);\n"
    "             drawTile(highlightTile);\n"
    "           }\n"
    "         }, 0);\n"
    "       }\n"
    "     }\n"
    "\n"
    "     function mouseX(evt) {\n"
    "       var x;\n"
    "\n"
    "       if (evt.pageX)\n"
    "         x = evt.pageX;\n"
    "       else\n"
    "         x = evt.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;\n"
    "\n"
    "       return x - evt.target.offsetLeft;\n"
    "     }\n"
    "\n"
    "     function mouseY(evt) {\n"
    "       var y;\n"
    "\n"
    "       if (evt.pageY)\n"
    "         y = evt.pageY;\n"
    "       else\n"
    "         y = evt.clientY + document.body.scrollTop + document.documentElement.scrollTop;\n"
    "\n"
    "       return y - evt.target.offsetTop;\n"
    "     }\n"
    "\n"
    "     // Keep track of a global 'mode' for each multi-frame asset to display in.\n"
    "     displayMode = {}\n"
    "     animFrame = {}\n"
    "     animTimers = {}\n"
    "\n"
    "     function toggleDisplayMode(firstId, idCount, mode) {\n"
    "       if (displayMode[firstId] == mode)\n"
    "         mode = null;\n"
    "\n"
    "       displayMode[firstId] = mode;\n"
    "\n"
    "       if (mode == \"anim\" || mode == \"all\") {\n"
    "         // Animation sequence only resets on \"play\". When paused, we intentionally\n"
    "         // keep the last previous frame visible. (Play/Pause behaviour)\n"
    "         animFrame[firstId] = 0;\n"
    "       }\n"
    "\n"
    "       document.getElementById(\"buttonAll\" + firstId).className = (mode == \"all\") ? \"button buttonOn\" : \"button\";\n"
    "       document.getElementById(\"buttonAnim\" + firstId).className = (mode == \"anim\") ? \"button buttonOn\" : \"button\";\n"
    "\n"
    "       updateVisibility(firstId, idCount);\n"
    "\n"
    "       if (animTimers[firstId]) {\n"
    "         clearInterval(animTimers[firstId]);\n"
    "         animTimers[firstId] = null;\n"
    "       }\n"
    "       if (mode == \"anim\") {\n"
    "         animTimers[firstId] = setInterval(function() { updateVisibility(firstId, idCount); }, 100);\n"
    "       }\n"
    "     }\n"
    "\n"
    "     function updateVisibility(firstId, idCount) {\n"
    "       var mode = displayMode[firstId];\n"
    "       var frame = animFrame[firstId];\n"
    "\n"
    "       if (mode == \"anim\") {\n"
    "         frame = (frame + 1) % idCount;\n"
    "         animFrame[firstId] = frame;\n"
    "       }\n"
    "\n"
    "       for (var i = 0; i < idCount; i++) {\n"
    "         var visible = mode == \"all\" ? true : frame == i;\n"
    "         document.getElementById(\"i\" + (firstId + i)).style.display = visible ? \"inline\" : \"none\";\n"
    "       }\n"
    "     }\n"
    "\n"
    "  </script>\n"
    "  <style> \n"
    " \n"
    "    body { \n"
    "      color: #eee; \n"
    "      background: #222; \n"
    "      font-family: verdana, tahoma, helvetica, arial, sans-serif; \n"
    "      font-size: 12px; \n"
    "      margin: 10px 5px 50px 5px; \n"
    "    } \n"
    "  \n"
    "    h1 { \n"
    "      background: #fff; \n"
    "      color: #222; \n"
    "      font-size: 22px; \n"
    "      font-weight: normal; \n"
    "      padding: 10px; \n"
    "      margin: 0; \n"
    "    } \n"
    " \n"
    "    h2 { \n"
    "      color: #fff; \n"
    "      font-size: 16px; \n"
    "      font-weight: normal; \n"
    "      padding: 10px; \n"
    "      margin: 0; \n"
    "    } \n"
    " \n"
    "    p { \n"
    "      padding: 0 10px; \n"
    "    } \n"
    "\n"
    "    canvas {\n"
    "      padding: 0;\n"
    "      margin: 0;\n"
    "    }\n"
    "\n"
    "    span.button {\n"
    "      -webkit-user-select: none;\n"
    "      -khtml-user-select: none;\n"
    "      -moz-user-select: none;\n"
    "      -o-user-select: none;\n"
    "      user-select: none;\n"
    "      cursor: pointer;\n"
    "\n"
    "      vertical-align: middle;\n"
    "      font-size: 12px; \n"
    "      margin: 0 0 0 2px;\n"
    "      padding: 1px 5px;\n"
    "      background: #555;\n"
    "      color: #000;\n"
    "    }\n"
    "\n"
    "    span.buttonOn {\n"
    "      background: #fb7;\n"
    "    }\n"
    " \n"
    "    span.button:hover {\n"
    "      background: #888;\n"
    "    }\n"
    "\n"
    "    span.buttonOn:hover {\n"
    "      background: #fda;\n"
    "    }\n"
    "\n"
    "    span.button:first-child {\n"
    "      margin: 0 0 0 12px;\n"
    "    }\n"
    "\n"
    "  </style> \n"
    "</head> \n"
    "<body onload=\"onload()\">\n"
    "\n";
