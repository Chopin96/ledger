
// const eos = Eos({ 
//   httpEndpoint: process.env.EOS_PROTOCOL + "://" +  process.env.EOS_HOST + ":" + process.env.EOS_PORT,
//   keyProvider: process.env.EOS_KEY,
//   chainId: process.env.EOS_CHAIN,
//   verbose:false,
//   logger: {
//     log: null,
//     error: null
//   }
// });

// eos.getAccount("eostitanvote")
// .then(result=>{

//     var command = 'cleos -u http://api.eostitan.com system voteproducer prods eostitanvote ' + result.voter_info.producers.join(" ");

//     console.log(command);

// })

Eos = require('eosjs')
config = {
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
  keyProvider: '5KfpCFGR8SBZ3At7oGTDcHgzXgCZRGV6hCT7DTfReYQ63gi3gQz', // WIF string or array of keys..
  httpEndpoint: 'http://ec2-35-183-119-153.ca-central-1.compute.amazonaws.com:8888',
    debug: false,
    expireInSeconds: 60,
  //broadcast: true,
  //verbose: false,
  logger: {
    log: null,
    error: null
  },
//  sign: true,
}

eos = Eos(config)

eos.contract('vtxledger').then(vtxledger =>{ vtxledger.getblnc(
        {
        "account":"Trust",
        "tokey":"EOS86MP9B9HgSfj8H7ZJtYGziiBMAxq5Z8a3FYnw1ACudHqUYV4uL",
        },
        {
         'authorization':['vtxledger@active']
        }).then(result =>{console.log(JSON.stringify(result,null,2))})
      }
)


  // eos.contract('stdledger').then(stdledger => stdledger.write(
  //         {
  //         "account":"test",
  //         "key":"EOS86MP9B9HgSfj8H7ZJtYGziiBMAxq5Z8a3FYnw1ACudHqUYV4uL",
  //         "value":"test",
  //         },
  //         {
  //          "authorization":["stdledger@active"]
  //         }
  // ).console.log())


