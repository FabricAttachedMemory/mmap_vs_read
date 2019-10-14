### mmap_vs_read

 This project is an attempt to benchmark "mmap" and "read" operation running in memory vs IO and The Machine (fabric) vs conventional systems.

###### NOTE: it has been wrote ran in May, 2018. The documentation was added in October, 2019, so the details are fuzzy. The project can be considered "deprecated".

### Results

10 Iterations.
3 types of hardware with 2 variations (1gb and 2gb dataset).

| Hardware Type        | mmap (avg T)  | read (avg T)  |
| -------------------- |:-------------:|--------------:|
| Laptop (1gb)         | 0.0489127     | 0.2228779 |
| Laptop (2gb)         | 0.0915907     | 0.4449868 |
| FTC Node (1gb)       | 0.0097628     | 0.6343705 |
| FTC Node (2gb)       | 0.185885      | 1.2684315 |
| Superdome (1gb)      | 0.0791239     | 0.6437892 |
| Superdome (2gb)      | 0.0185885     | 1.2684315 |

##### Raw data

[logs and hardware specs here](https://github.com/FabricAttachedMemory/mmap_vs_read/tree/master/log)

Laptop(1gb) mmap
###### 0.050523 + 0.052861 + 0.046087 + 0.046248 + 0.050785 + 0.050685 + 0.046944 + 0.046527 + 0.050756 + 0.047711

Laptop(1gb) read
###### 0.222648 + 0.230720 + 0.226624 + 0.223131 + 0.218647 + 0.222995 + 0.222622 + 0.222750 + 0.222642 + 0.216000

Laptop(2gb) mmap
###### 0.092000 + 0.091084 + 0.095576 + 0.092000 + 0.092000 + 0.091678 + 0.088913 + 0.088656 + 0.088000 + 0.096000

Laptop(2gb) read

###### 0.451837 + 0.449228 + 0.443800 + 0.445230 + 0.443678 + 0.440000 + 0.443482 + 0.444000 + 0.447459 + 0.441154

FTC Node (1gb) mmap
###### 0.011789 + 0.009509 + 0.009851 + 0.009498 + 0.009765 + 0.009433 + 0.009387 + 0.009419 + 0.009559 + 0.009418

FTC Node (1gb) read
###### 0.637951 + 0.633739 + 0.634947 + 0.633837 + 0.633912 + 0.634166 + 0.634876 + 0.634599 + 0.633107 + 0.632571

FTC Node (2gb) mmap
###### 0.024263 + 0.016970 + 0.016817 + 0.018813 + 0.018801 + 0.019037 + 0.016693 + 0.016618 + 0.018707 + 0.019166

FTC Node (2gb) read
###### 1.274407 + 1.269337 + 1.267647 + 1.269114 + 1.266879 + 1.266753 + 1.265751 + 1.268945 + 1.266774 + 1.268708

Superdome (1gb) mmap
###### 0.099432 + 0.076609 + 0.074840 + 0.077939 + 0.066186 + 0.078938 + 0.079500 + 0.076505 + 0.077273 + 0.084017

Superdome (1gb) read
###### 0.606572 + 0.601967 + 0.713890 + 0.590326 + 0.672340 + 0.609142 + 0.714261 + 0.579411 + 0.673609 + 0.676374

Superdome (2gb) mmap
###### 0.024263 + 0.016970 + 0.016817 + 0.018813 + 0.018801 + 0.019037 + 0.016693 + 0.016618 + 0.018707 + 0.019166

Superdome (2gb) read
###### 1.274407 + 1.269337 + 1.267647 + 1.269114 + 1.266879 + 1.266753 + 1.265751 + 1.268945 + 1.266774 + 1.268708
