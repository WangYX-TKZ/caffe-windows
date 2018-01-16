#ifndef CAFFE_LABEL_SPECIFIC_AFFINE_LAYER_HPP_
#define CAFFE_LABEL_SPECIFIC_AFFINE_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace caffe {

template <typename Dtype>
class LabelSpecificAffineLayer : public Layer<Dtype> {
 public:
  explicit LabelSpecificAffineLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
                          const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
                       const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "LabelSpecificAffine"; }
  virtual inline int MinNumBottomBlobs() const { return 2; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  virtual Dtype CalcLSE(const vector<Blob<Dtype>*>& bottom,
                        Blob<Dtype>* LSE);
  virtual Dtype MeanTargetLogit(const vector<Blob<Dtype>*>& bottom);
  virtual Dtype MeanMaxNegativeLogit(const vector<Blob<Dtype>*>& bottom);

  Dtype scale_base_;
  Dtype scale_gamma_;
  Dtype scale_power_;
  Dtype scale_min_;
  Dtype scale_max_;
  Dtype bias_base_;
  Dtype bias_gamma_;
  Dtype bias_power_;
  Dtype bias_min_;
  Dtype bias_max_;
  Dtype power_base_;
  Dtype power_gamma_;
  Dtype power_power_;
  Dtype power_min_;
  Dtype power_max_;
  Dtype scale_factor_;
  bool protect_low_bound_;
  bool transform_test_;
  int iteration_;
  bool auto_tune_;
  bool reset_;
  bool original_bp_;
  Dtype scale, bias, power;
  Blob<Dtype> selected_value_;
  Blob<Dtype> sum_multiplier_;
  Blob<double> sum_multiplier_channel_;
  Blob<Dtype> lower_bound_;
};

}  // namespace caffe

#endif  // CAFFE_LABEL_SPECIFIC_AFFINE_LAYER_HPP_
