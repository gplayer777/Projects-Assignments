from collections import OrderedDict
from operator import itemgetter
import urllib
import requests
from bs4 import BeautifulSoup
from bs4.element import Comment
from collections import Counter
from string import punctuation
import re
from multiprocessing import Pool
import multiprocessing
from collections import deque
import math
import concurrent
import nltk




WORDS = {}
visited = set()
S = []


def make_soup(url):

  result = requests.get(url)
  src = result.content
  soup_data = BeautifulSoup(src, "html.parser")
  return soup_data


def tag_visible(element):
    if element.parent.name in ['style', 'script', 'head', 'title', 'meta', '[document]']:
        return False
    if isinstance(element, Comment):
        return False
    return True


def text_from_html(url):
    soup = make_soup(url)
    if soup == -1:
        return ''
    texts = soup.findAll(text=True)
    visible_texts = filter(tag_visible, texts)
    return " ".join(t.strip() for t in visible_texts)



def get_words(url):
    text = text_from_html(url)

    text = [re.sub('\W+', '', t) for t in text.lower().split()]
    text = list(filter(lambda t: len(t), text))
    return text



def get_hrefs(url):
    soup = make_soup(url)
    if soup == -1:
        return []

    hrefs = []

    for link in soup.find_all('a'):
        hrefs.append(link.get('href'))

    ans = []
    for link in hrefs:
        if link is None or len(link) == 0:
            continue
        if link.find('https') != -1 or link.find('http') != -1:
            ans.append(link)
        else:
            sub_sites = link.split('/')
            if len(sub_sites) > 1:
                key_word = '/' + sub_sites[1] + '/'
                pos = url.find(key_word)
                if pos != -1:
                    ans.append(url[:pos] + link)
                else:
                    ans.append(url + link)

    return ans

def get_dict():
   return dict(sorted(WORDS.items(), key=lambda x: len(x[1]), reverse=True))


def search_for_sentences(word, url):
    text = text_from_html(url)
    sentences = nltk.sent_tokenize(text)
    result = [sentence for sentence in sentences if word in sentence]
    S.append((url, result))


def get_multi_dict():
    return dict(sorted(WORDS.items(), key=lambda x: x[1], reverse=True))

def BFS_multi(url, max_steps):
    sites = [url]
    all_sites = [url]

    for no in range(max_steps):
        act_sites = []
        # Use ProcessPoolExecutor or ThreadPoolExecutor
        with concurrent.futures.ThreadPoolExecutor() as executor:
            act_sites = list(executor.map(get_hrefs, sites))
            print(sites)
            print(act_sites[0])
        sites = act_sites[0]
        all_sites += act_sites[0]

    sites = all_sites
    words = []

    print('\n Start scrapping \n')


    with concurrent.futures.ThreadPoolExecutor() as executor:
        words = list(executor.map(get_words, sites))

    for word_list in words:
        for w in word_list:
           WORDS[w] = WORDS.get(w, 0) + 1

    print('\n\n---SITES---\n\n')
    for i, s in enumerate(sites):
        print(f'{i} / {len(sites)} -> : ', s)

def multi_scrap(url, depth):
    WORDS.clear()
    BFS_multi(url, depth)
    return get_multi_dict()


site = 'https://en.wikipedia.org/wiki/Python_Software_Foundation'
site2 = 'https://en.wikipedia.org/wiki/Python_(programming_language)'
site3 = 'https://en.wikipedia.org/wiki/Python'




words = multi_scrap(site3, 1)


pair = next(iter(words.items()))
print(f'word  \'{pair[0]}\'  {pair[1]} times!')
