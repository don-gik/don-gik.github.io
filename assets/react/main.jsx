import React, { Suspense, useRef } from 'react';
import { createRoot } from 'react-dom/client';
import { Canvas, useFrame } from '@react-three/fiber';

function SpinningBox(props) {
  const ref = useRef();
  useFrame((state, delta) => {
    if (ref.current) {
      ref.current.rotation.x += delta * 0.5;
      ref.current.rotation.y += delta * 0.7;
    }
  });
  return (
    <mesh ref={ref} {...props}>
      <boxGeometry args={[1, 1, 1]} />
      <meshStandardMaterial color="#61dafb" />
    </mesh>
  );
}

function Scene() {
  return (
    <Canvas camera={{ position: [2.5, 2, 2.5], fov: 60 }}>
      <ambientLight intensity={0.5} />
      <pointLight position={[5, 5, 5]} intensity={1} />
      <Suspense fallback={null}>
        <SpinningBox position={[0, 0, 0]} />
      </Suspense>
    </Canvas>
  );
}

function mountAll() {
  const nodes = document.querySelectorAll('[data-r3f-canvas]');
  nodes.forEach((el) => {
    // Avoid double mount
    if (el.__r3fMounted) return;
    el.__r3fMounted = true;
    const root = createRoot(el);
    root.render(<Scene />);
  });
}

// Auto-mount on DOM ready
if (document.readyState === 'loading') {
  document.addEventListener('DOMContentLoaded', mountAll);
} else {
  mountAll();
}

// Optional: expose manual mount
window.SiteReactApp = { mountAll };

