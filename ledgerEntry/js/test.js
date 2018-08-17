Eos = require('eosjs')

// Default configuration
config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: '5KfpCFGR8SBZ3At7oGTDcHgzXgCZRGV6hCT7DTfReYQ63gi3gQz', // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
  expireInSeconds: 60,
  broadcast: true,
  verbose: true, // API activity
  sign: true
}

eos = Eos(config)

/*eos.contract('test').then(

	test => test.rcrdtrf()

)*/

eos.contract('test').then(test => test.rcrdtrf(
	{
    "s": "test",
    "fromAccount": "Distribution",
    "toAccount": "Trust",
    "fromKey": 1234,
    "toKey": 1234,
    "amount": 1234
},
	{
	 authorization: [ `test@active` ] 
	
	}
).catch())

