Eos = require('eosjs')
config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: '5KfpCFGR8SBZ3At7oGTDcHgzXgCZRGV6hCT7DTfReYQ63gi3gQz', // WIF string or array of keys..
  httpEndpoint: 'http://ec2-35-183-119-153.ca-central-1.compute.amazonaws.com:8888',
        debug: true,
    expireInSeconds: 60,
  broadcast: true,
  verbose: true,
  sign: true,
}

eos = Eos(config)

eos.contract('vtxledger').then(vtxledger => vtxledger.rcrdtfr(
        {"s":"vtxledger",
        "fromaccount":"Distribution",
        "toaccount":"Trust",
        "fromkey":"1234",
        "tokey":"1234",
        "amount":1234},
        {
         'authorization':['vtxledger@active']
        }
))
