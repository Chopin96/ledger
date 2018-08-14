import subprocess
import os
import platform
import re
import shutil
import requests
import json
import random

home = os.environ['HOME']
os.environ['EOS_SOURCE'] = home + "/eos"
if platform.system() == 'Darwin':
    os.environ['NODEOS_DATA'] = home + "/Library/Application\ Support/eosio/nodeos/data"
elif platform.system() == 'Linux':
    os.environ['NODEOS_DATA'] = home + "/.local/share/eosio/nodeos/data/"
os.environ['EOS_NODEOS'] = "/usr/local/eosio/bin/nodeos"
os.environ['EOS_KEOSD'] = "/usr/local/eosio/bin/keosd"
os.environ['CLEOS'] = "/usr/local/eosio/bin/cleos"

class BlockChain():
    def __init__(self):
        self.producer = "https://api.eosnewyork.io:443"

class Account():
    def __init__(self):
        self.name = ""
        self.creator = ""
        self.receiver = ""
        self.creatorOwnerKey = ""
        self.creatorActiveKey = ""
        self.cpu = ""
        self.bandwidth = ""
        self.ram = ""

class Wallet():
    def __init__(self):
        self.name = ""
        self.key = ""
        self.ownerPrivateKey = ''
        self.ownerPublicKey = ''
        self.activePrivateKey = ''
        self.activePublicKey = ''

    def erasePrivateKeys(self):
        self.ownerPrivateKey = ""
        self.activePrivateKey = ""

class Order():

    def __init__(self):
        self.to = ""
        self.amount = 0.0000
        self.contract = ""
        self.currency = ""
        self.contractAccountName = ""
        self.stakeCPU = ""
        self.stakeBandWidth = ""
        self.buyRam = 0

    def reset(self):
        self.to = ""
        self.amount = 0.0000
        self.contract = ""
        self.currency = ""
        self.contractAccountName = ""

def setOwnerKeys():
    out = subprocess.check_output(["/usr/local/eosio/bin/cleos", "create", "key"])
    key = out[13:]
    key = key[:-67]
    key2 = out[77:]
    key2 = key2[:-1]
    wallet.ownerPrivateKey = key
    wallet.ownerPublicKey = key2
    print('Owner keys set')

def setActiveKeys():
    out = subprocess.check_output(["/usr/local/eosio/bin/cleos", "create", "key"])
    key = out[13:]
    key = key[:-67]
    key2 = out[77:]
    key2 = key2[:-1]
    wallet.activePrivateKey = key
    wallet.activePublicKey = key2
    print('Active keys set')

def importKeys():
    out = subprocess.check_output(['/usr/local/eosio/bin/cleos', 'wallet', 'import', '-n', wallet.name, '--private-key', wallet.ownerPrivateKey])
    out1 = subprocess.check_output(['/usr/local/eosio/bin/cleos', 'wallet', 'import', '-n', wallet.name, '--private-key', wallet.activePrivateKey])
    wallet.erasePrivateKeys()
    print('Keys imported to wallet')

def createWallet(name):
    walletDirectory = os.environ['HOME'] + '/eosio-wallet'
    if not os.path.exists(walletDirectory):
        os.makedirs(walletDirectory)
    out = subprocess.check_output(['/usr/local/eosio/bin/cleos', 'wallet', 'create', '-n', name])
    print(str(out))

def setContractSteps():
    out = ''
    try:
        out = subprocess.check_output([os.environ['CLEOS'], 'set', 'contract', account.name, order.contract, '-p', account.name])
    except:
        out = 'Cannot set contract steps'
    print(str(out))

def rcrdtrf():
    flushWallets()
    createEosioWallet()
    wallet.name = 'test'
    createWallet('test')
    setActiveKeys()
    setOwnerKeys()
    importKeys()
    account.name = 'test'
    createAccount()
    order.contract = os.environ['HOME'] + '/ledger/ledgerEntry/'
    setContractSteps()
    object = '["test","distribution","trust","EOS76eN25dUZqb33cA7pPSXEbBFuxwxopNCLnaWFKNviu5dcig6yJ", "EOS62L2r4FqnCbHAspPS3KBByGa728G3UDYxGkTY15mad97M4JhzN", 50]'
    out = subprocess.check_output([os.environ['CLEOS'], 'push', 'action', account.name, 'rcrdtfr', object, '-p', account.name + '@active'])
    print(str(out))

def getrcrd():
    out = subprocess.check_output([os.environ['CLEOS'], 'push', 'action', account.name, 'getrcrd', '["EOS62L2r4FqnCbHAspPS3KBByGa728G3UDYxGkTY15mad97M4JhzN"]' , '-p', account.name + '@active'])
    print(str(out))

def createEosioWallet():
    out = ''
    try:
        wallet.name = 'eosio'
        createWallet('eosio')
        setOwnerKeys()
        setActiveKeys()
        out = subprocess.check_output([os.environ['CLEOS'], 'wallet', 'import', '-n', 'eosio', '--private-key', '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'])
    except:
        out = 'could not create wallet'
    print(str(out))


def check_kill_process(pstring):
    for line in os.popen("ps ax | grep " + pstring + " | grep -v grep"):
        fields = line.split()
        pid = fields[0]
    if pid > 0:
        os.kill(int(pid), signal.SIGKILL)


def flushWallets():
    rand = random.randint(1, 1000000)
    try:
        subprocess.check_output(['mv', os.environ['HOME'] + '/eosio-wallet/', os.environ['HOME'] + '/eosio-wallet.save' + str(rand)])
        #check_kill_process(os.environ['EOS_KEOSD'])
    except:
        print('Could not move')


def createAccount():
    out = ''
    try:
        out = subprocess.check_output([os.environ['CLEOS'], 'create', 'account', 'eosio', account.name, wallet.ownerPublicKey, wallet.activePublicKey, '-p', 'eosio'])
    except:
        out = 'Could not create account'
    print(str(out))


if __name__ == '__main__':
    account = Account()
    wallet = Wallet()
    blockchain = BlockChain()
    order = Order()
    rcrdtrf()
    getrcrd()


