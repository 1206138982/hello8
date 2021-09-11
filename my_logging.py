import logging

logger = ''

def init_log():
    global logger
    # logging.basicConfig(filename='logs.log', filemode='w',format='%(levelname)s -> %(asctime)s: %(message)s', level=logging.DEBUG)
    logging.basicConfig(filename='logs.log', filemode='w',format='%(levelname)s -> %(asctime)s: %(message)s', level=logging.INFO)
    logger = logging.getLogger(__name__)
    save_log('init log success')

def save_log(str):
    logger.info(str)

##log reference:
##https://blog.csdn.net/cunchi4221/article/details/107474136?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163134201316780264076716%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163134201316780264076716&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-107474136.pc_search_result_control_group&utm_term=python%E8%AE%B0%E5%BD%95log%E6%97%A5%E5%BF%97&spm=1018.2226.3001.4187
