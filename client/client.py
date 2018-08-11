#!/usr/bin/python3
# -*- coding: UTF-8 -*-
#
# References:
# - [Mac OSX python ssl.SSLError: [SSL: CERTIFICATE_VERIFY_FAILED] certificate verify failed (_ssl.c:749)](https://stackoverflow.com/questions/42098126/mac-osx-python-ssl-sslerror-ssl-certificate-verify-failed-certificate-verify)

from AMC import *
import urllib.request


def main():
    url = 'https://andrewmc.cn/cgi-bin'

    request = urllib.request.Request(url)
    response = urllib.request.urlopen(request)

    log.info('response:\n<START>\n%s\n<END>' % response.read().decode())

    log.debug('done')
    return


if __name__ == '__main__':
    # sys.settrace(trace)
    log.console_level = log.LOG_DEBUG
    ret = main()

    if ret is None:
        ret = 0
    sys.exit(ret)
