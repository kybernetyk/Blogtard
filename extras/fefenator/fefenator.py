#!/usr/bin/env python

import urllib2
import BeautifulSoup
from xgoogle import translate

# read blog
res = urllib2.urlopen("http://blog.fefe.de")
html = res.read();

#parse
soup = BeautifulSoup.BeautifulSoup(html)

lis = soup.findAll('li')

outhtml = "<html><head><meta http-equiv="content-type" content="text/html; charset=UTF-8"><title>THE BEST BLOG IN THE UNIVERSE WITHOUT COMMENTS BECAUSE USER GENERATED CONTENT IS RETARDED! DIE AND LISTEN TO THE FUHRER!</head><body>"
outhtml += "<h1>This is my new blog!</h1><p><b>I have make a blog - just like fefe only in english because krautspeak is for retards!</b></p>"
		
outhtml += "<ul>"
for li in lis:
	text = li.text
	try:
		trans_text = translate.Translator().translate(text.encode('utf-8'), lang_from="de", lang_to="en");
		outhtml += "\t<li><p>%s</p></li>\n\n" % (trans_text)
	except:
		pass
outhtml += "</ul></body></html>";


print outhtml.encode('utf-8')
