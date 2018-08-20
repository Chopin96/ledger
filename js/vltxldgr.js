exports.config = function (chainid, keyprovider, httpendpoint, expire, broadcast, verbose, sign) {
    config = {
        'chainId': chainid,
        'keyProvider': keyprovider,
        'httpEndpoint': httpendpoint,
        'expireInSeconds': expire,
        'broadcast': broadcast,
        'verbose': verbose,
        'sign': sign,
    }
    return config;
}

exports.rcrdtrf = function (eos, contract, fromaccount, toaccount, fromkey, tokey, amount) {
    eos.contract('test').then(test => test.rcrdtrf(
        {
            "s": contract,
            "fromAccount": fromaccount,
            "toAccount": toaccount,
            "fromKey": fromkey,
            "toKey": tokey,
            "amount": amount,
        },
        {
            authorization: [`test@active`]
        }
    ).catch())
}

