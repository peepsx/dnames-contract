# dnames Contract
This is the repository for the official dNames contract, used for adding, modifying, and deleting records related to dNames dTLDs. It is used by the [dNames App](https://github.com/peepsx/dnames-app).

### Contract Actions
This contract includes the following actions:

#### ```add```
The ```add``` action is used for either adding or modifying dDNS records related to a dNames dTLD. If a ```record_name``` for a ```domain``` (key) already exists, then the ```modify``` function is ran. If a ```record_name``` for a ```domain``` (key) does not exist, it is added to the ARISEN database, along with the record's ```dweb_key```.

##### ```add``` Parameters
The ```add``` action has the following parameters:
- ```domain``` - The domain the record is being added to or modified for.
- ```record_name``` - String of the record name. The ```root``` record, signifies it is the record for the root domain and not a sub-domain (domain.dcom and not sub.domain.dcom).
- ```dweb_key``` - String of the dDrive key. This is considered to be the record's host.

#### ```erase``` 
The ```erase``` action is used for removing a record for a dNames dTLD. The ```record_name``` for a given ```domain``` must exist for the ```erase``` action to work. 

##### ```erase``` Parameters
- ```domain``` - The domain a record is being removed for.
- ```record_name``` - String of a record name that is being removed.

### Interacting With Contract
You can add, modify and erase records for a dNames dTLD using [arisecli](https://arisen.network/arisecli), by following the instructions below:

#### Adding A Record
You can add a record by running the following command:

```
arisecli push action dnames add '["peeps.dcom", "dwww", "8fade7a4bf7de59..."]' -p peeps.dcom@active
```

This creates a record for ```dwww.peeps.dcom``` and points to the above dWeb (dDrive) key. You could create the "root" record, rather than the "dwww" record so that browsers like [dBrowser](http://dbrowser.com) will allow the above dWeb key to be accessed with the root domain (dweb://peeps.dcom).

#### Removing A Record
You can remove a record by running the following command:

```
arisecli push action dnames erase '["peeps.dcom", "dwww"]' -p peeps.dcom@active
```

This removes the dwww record added above.

### To-Do
- Add a function for limiting the ```add``` action ```domain``` parameter to just dNames dTLDs, so that the dnames database isn't filled with spam.
- Create ```dnames-dns``` Node.JS library for performing dDNS lookups via this contract on ARISEN.
- Create API for interacting with dNames contract, so that ArisenJS doesn't have to be used directly.
- Add a function for checking for the existence of a dTLD, before running the ```add``` or ```erase``` actions.

### LICENSE
[MIT](LICENSE.md)

### Credit 
This contract was written by Jared Rice Sr from his jail cell, on notebook paper, before it was transcribed and subsequently uploaded to GitHub.

### Copyright
Copyright 2020 Peeps. All rights reserved.