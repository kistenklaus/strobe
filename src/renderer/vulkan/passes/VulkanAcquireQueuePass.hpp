#pragma once
#include "renderer/RenderPass.hpp"
#include "renderer/vulkan/VulkanRendererBackend.hpp"

namespace sge::vulkan {

enum VulkanQueueAcquireTarget { GRAPHICS_QUEUE, COMPUTE_QUEUE, TRANSFER_QUEUE };

class VulkanAcquireQueuePass : public RenderPass {
 public:
  VulkanAcquireQueuePass(VulkanRendererBackend* renderer,
                         VulkanQueueAcquireTarget queueType = GRAPHICS_QUEUE);

  void execute() override;

  u32 getQueueSource() { return m_queueSource; }

 private:
  const u32 m_queueType;
  const u32 m_queueSource;
};

}  // namespace sge::vulkan